//
// Created by desrumaux on 25/08/2021.
//

#include "JsonPath.hpp"

#include <stdexcept>
#include <stack>

#include "PocoJsonPath/Helpers/JsonHelper.hpp"
#include "PocoJsonPath/Operators/IOperator.hpp"

namespace PocoJsonPath {

    std::unique_ptr<peg::parser> JsonPath::parser;

    void JsonPath::Initialize()
    {
        if (!JsonPath::IsInitialized()) {
            JsonPath::parser = std::make_unique<peg::parser>(R"(
                ROOT_QUERY                  <- ROOT QUERY_OPERATIONS PIPE*
                QUERY                       <- INIT QUERY_OPERATIONS PIPE*
                QUERY_OPERATIONS            <- (FILTER/INDEX/DYNAMIC_INDEX/CHILDREN)*
                PIPE                        <- '|' PIPE_NAME '(' QUERY (',' QUERY)* ')' / '|' PIPE_NAME '(' ')' / '|' PIPE_NAME
                PIPE_NAME                   <- < [A-Za-z] [A-Za-z0-9_]* >
                INIT                        <- ROOT / CURRENT
                FILTER                      <- '[' '?' '(' QUERY_WHERE ')' ']'
                QUERY_WHERE                 <- '(' (QUERY_WHERE/QUERY/VALUE) ')' OPERATOR '(' (QUERY_WHERE/QUERY/VALUE) ')'  / '(' (QUERY_WHERE/QUERY/VALUE) ')' OPERATOR (QUERY_WHERE/QUERY/VALUE) / (QUERY/VALUE) OPERATOR '(' (QUERY_WHERE/QUERY/VALUE) ')' / (QUERY/VALUE) OPERATOR (QUERY_WHERE/QUERY/VALUE) / '(' (QUERY_WHERE/QUERY/VALUE) ')'
                OPERATOR                    <- '==' / '!=' / '>=' / '>' / '<=' / '<' / '&&' / '||'
                INDEX                       <- '[' (STRING/INDEX_KEYWORD_NUMBER) (',' (STRING/INDEX_KEYWORD_NUMBER))* ']' / '.' INDEX_KEYWORD
                DYNAMIC_INDEX               <- '[' '(' QUERY ')' ']'
                CHILDREN                    <- '..' INDEX_KEYWORD
                INDEX_KEYWORD               <- INDEX_KEYWORD_STRING / INDEX_KEYWORD_NUMBER / INDEX_KEYWORD_WILDCARD
                INDEX_KEYWORD_STRING        <- < [A-Za-z_$] [A-Za-z0-9_$]* >
                INDEX_KEYWORD_NUMBER        <- < [0-9]+ >
                INDEX_KEYWORD_WILDCARD      <- '*'
                VALUE                       <- STRING / NUMBER
                STRING                      <- < '"' (ESCAPE_STRING_CHARACTER/STRING_CHARACTER_DQUOTE)* '"' > / < "'" (ESCAPE_STRING_CHARACTER/STRING_CHARACTER_SQUOTE)* "'" >
                ESCAPE_STRING_CHARACTER     <- < '\\' . >
                STRING_CHARACTER_DQUOTE     <- < [^"] >
                STRING_CHARACTER_SQUOTE     <- < [^'] >
                NUMBER                      <- [0-9]+ / [0-9]+[.][0-9]+
                ROOT                        <- '$'
                CURRENT                     <- '@'
                %whitespace                 <- [ \n]*
            )");

            if (!static_cast<bool>(*JsonPath::parser)) {
                JsonPath::parser.reset();
                throw std::logic_error("JsonPath parser failed to create the parser.");
            }

            auto& ref = *parser;
            ref.enable_packrat_parsing();
            ref["CURRENT"] = [](const peg::SemanticValues &vs) {
                return PathFunction([](JsonPathScope& scope) -> Poco::Dynamic::Var {
                    return scope.getCurrent();
                });
            };

            ref["ROOT"] = [](const peg::SemanticValues &vs) {
                return PathFunction([](JsonPathScope& scope) -> Poco::Dynamic::Var {
                    return scope.getRoot();
                });
            };

            ref["NUMBER"] = [](const peg::SemanticValues &vs) {
                double value = std::stod(vs.token_to_string());
                return Poco::Dynamic::Var{value};
            };

            ref["STRING"] = [](const peg::SemanticValues &vs) {
                std::string value = vs.token_to_string();
                value = value.substr(1, value.length() - 2);
                return Poco::Dynamic::Var{value};
            };

            ref["INDEX_KEYWORD_WILDCARD"] = [](const peg::SemanticValues &vs) {
                return Poco::Dynamic::Var{"*"};
            };

            ref["INDEX_KEYWORD_NUMBER"] = [](const peg::SemanticValues &vs) {
                long value = std::stol(vs.token_to_string());
                return Poco::Dynamic::Var{value};
            };

            ref["INDEX_KEYWORD_STRING"] = [](const peg::SemanticValues &vs) {
                std::string value = vs.token_to_string();
                return Poco::Dynamic::Var{value};
            };

            ref["CHILDREN"] = [](const peg::SemanticValues &vs) {
                auto keyword = std::any_cast<Poco::Dynamic::Var>(vs[0]);
                if (keyword.isString()) {
                    std::string strKeyword = keyword.extract<std::string>();
                    if ("*" == strKeyword) {
                        return PathFunction([](JsonPathScope& scope) -> Poco::Dynamic::Var{
                            auto obj = Helpers::JsonHelper::castToJsonObject(scope.getCurrent());
                            if (obj.has_value()) {
                                Poco::JSON::Array::Ptr array{new Poco::JSON::Array};
                                for (auto name : (*obj)->getNames()) {
                                    array->add((*obj)->get(name));
                                }
                                return array;
                            }

                            auto arr = Helpers::JsonHelper::castToJsonArray(scope.getCurrent());
                            if (arr.has_value()) {
                                return arr.value();
                            }

                            return Poco::JSON::Array::Ptr{new Poco::JSON::Array};
                        });
                    } else {
                        return PathFunction([strKeyword](JsonPathScope& scope) -> Poco::Dynamic::Var {
                            Poco::JSON::Array::Ptr array{new Poco::JSON::Array};
                            std::stack<Poco::Dynamic::Var> vars;
                            vars.push(scope.getCurrent());
                            while (!vars.empty()) {
                                auto item = vars.top();
                                vars.pop();

                                auto obj = Helpers::JsonHelper::castToJsonObject(item);
                                if (obj.has_value()) {
                                    if (obj.value()->has(strKeyword)) {
                                        array->add(obj.value()->get(strKeyword));
                                    } else {
                                        for (auto name: obj.value()->getNames()) {
                                            vars.push(obj.value()->get(name));
                                        }
                                    }
                                    continue;
                                }

                                auto arr = Helpers::JsonHelper::castToJsonArray(item);
                                if (arr.has_value()) {
                                    for (auto item : **arr) {
                                        vars.push(item);
                                    }
                                    continue;
                                }
                            }
                            return array;
                        });
                    }
                } else {
                    long index = keyword.extract<long>();
                    std::ostringstream oss;
                    oss << index;
                    std::string indexStr = oss.str();
                    return PathFunction([index, indexStr](JsonPathScope& scope) -> Poco::Dynamic::Var {
                        Poco::JSON::Array::Ptr array{new Poco::JSON::Array};
                        std::stack<Poco::Dynamic::Var> vars;
                        vars.push(scope.getCurrent());
                        while (!vars.empty()) {
                            auto item = vars.top();
                            vars.pop();

                            auto obj = Helpers::JsonHelper::castToJsonObject(item);
                            if (obj.has_value()) {
                                if (obj.value()->has(indexStr)) {
                                    array->add(obj.value()->get(indexStr));
                                } else {
                                    for (auto name: obj.value()->getNames()) {
                                        vars.push(obj.value()->get(name));
                                    }
                                }
                                continue;
                            }

                            auto arr = Helpers::JsonHelper::castToJsonArray(item);
                            if (arr.has_value()) {
                                if ((*arr)->size() > index) {
                                    array->add((*arr)->get(index));
                                } else {
                                    array->add(Poco::Dynamic::Var{});
                                }
                                continue;
                            }
                        }
                        return array;
                    });
                }
            };

            ref["DYNAMIC_INDEX"] = [](const peg::SemanticValues &vs) {
                return PathFunction([](JsonPathScope& scope) {
                    // TODO dynamic index
                    return scope.getCurrent();
                });
            };

            ref["INDEX"] = [](const peg::SemanticValues &vs) {
                std::function<PathFunction(Poco::Dynamic::Var)> fn{[](Poco::Dynamic::Var var) -> PathFunction {
                    std::string key;
                    std::optional<long> index = var.isString() ? std::nullopt : std::make_optional(var.extract<long>());
                    if (index.has_value()) {
                        std::ostringstream oss;
                        oss << index.value();
                        key = oss.str();
                    } else {
                        key = var.extract<std::string>();
                    }

                    if ("*" != key) {
                        return PathFunction([index, key](JsonPathScope &scope) -> Poco::Dynamic::Var {
                            auto obj = Helpers::JsonHelper::castToJsonObject(scope.getCurrent());
                            if (obj.has_value()) {
                                return obj.value()->get(key);
                            }

                            if (index.has_value()) {
                                auto arr = Helpers::JsonHelper::castToJsonArray(scope.getCurrent());
                                if (arr.has_value() && arr.value()->size() > index.value()) {
                                    return arr.value()->get(index.value());
                                }
                            }

                            return Poco::Dynamic::Var{};
                        });
                    } else {
                        return PathFunction([key](JsonPathScope &scope) -> Poco::Dynamic::Var {
                            auto obj = Helpers::JsonHelper::castToJsonObject(scope.getCurrent());
                            if (obj.has_value()) {
                                return obj.value()->get(key);
                            }

//                            if (index.has_value()) {
//                                auto arr = Helpers::JsonHelper::castToJsonArray(scope.current);
//                                if (arr.has_value() && arr.value()->size() > index.value()) {
//                                    return arr.value()->get(index.value());
//                                }
//                            }

                            return Poco::Dynamic::Var{};
                        });
                    }
                }};

                if (vs.size() == 1) {
                    return fn(std::any_cast<Poco::Dynamic::Var>(vs[0]));
                } else {
                    std::vector<PathFunction> functions;
                    for (int i = 0; i < vs.size(); i++) {
                        functions.push_back(fn(std::any_cast<Poco::Dynamic::Var>(vs[i])));
                    }
                    return PathFunction([functions](JsonPathScope& scope) -> Poco::Dynamic::Var {
                        Poco::JSON::Array::Ptr array{new Poco::JSON::Array};
                        for (auto fn : functions) {
                            array->add(fn(scope));
                        }
                        return array;
                    });
                }
            };

            ref["OPERATOR"] = [](const peg::SemanticValues &vs) {
                auto op = vs.token_to_string();
                return OperatorFunction([op](JsonPathScope& scope, Poco::Dynamic::Var& leftMember, Poco::Dynamic::Var& rightMember) {
                    return scope.invokeOperator(op, leftMember, rightMember);
                });
            };

            ref["QUERY_WHERE"] = [](const peg::SemanticValues &vs) {
                auto leftMemberFn = std::any_cast<PathFunction>(vs[0]);
                auto operatorFn = std::any_cast<OperatorFunction>(vs[1]);
                auto rightMemberFn = std::any_cast<PathFunction>(vs[2]);
                return PathFunction([leftMemberFn, operatorFn, rightMemberFn](JsonPathScope& scope) {
                    auto leftMember = leftMemberFn(scope);
                    auto rightMember = rightMemberFn(scope);
                    return operatorFn(scope, leftMember, rightMember);
                });
            };

            ref["FILTER"] = [](const peg::SemanticValues &vs) {
                return PathFunction([](JsonPathScope& scope) {
                    // TODO filter
                    return scope.getCurrent();
                });
            };

            ref["PIPE_NAME"] = [](const peg::SemanticValues &vs) {
                return vs.token_to_string();
            };

            ref["PIPE"] = [](const peg::SemanticValues &vs) {
                auto pipeName = std::any_cast<std::string>(vs[0]);
                std::vector<PathFunction> functions;
                for (int i = 1; i < vs.size(); i++) {
                    functions.push_back(std::any_cast<PathFunction>(vs[i]));
                }
                return PathFunction([pipeName, functions](JsonPathScope& scope) -> Poco::Dynamic::Var {
                    std::vector<Poco::Dynamic::Var> parameters;
                    for (auto& fn : functions) {
                        parameters.push_back(fn(scope));
                    }
                    return scope.invokeFilter(pipeName, parameters);
                });
            };

            ref["QUERY_OPERATIONS"] = [](const peg::SemanticValues &vs) {
                std::vector<PathFunction> functions;
                for (int i = 0; i < vs.size(); i++) {
                    functions.push_back(std::any_cast<PathFunction>(vs[i]));
                }
                return PathFunction([functions](JsonPathScope& scope) {
                    Poco::Dynamic::Var result = scope.getCurrent();
                    for (int i = 0; i < functions.size(); i++) {
                        JsonPathScope currentScope{scope, result};
                        result = functions.at(i)(currentScope);
                    }
                    return result;
                });
            };

            std::function<PathFunction(const peg::SemanticValues &vs)> queryFn = [](const peg::SemanticValues &vs) {
                auto src = std::any_cast<PathFunction>(vs[0]);
                auto filter = std::any_cast<PathFunction>(vs[1]);
                return PathFunction([src, filter](JsonPathScope& rootScope) {
                    JsonPathScope scope{rootScope, src(rootScope)};
                    return filter(scope);
                });
            };
            ref["ROOT_QUERY"] = queryFn;
            ref["QUERY"] = queryFn;
        }
    }

    bool JsonPath::IsInitialized()
    {
        return nullptr != JsonPath::parser;
    }

    peg::parser& JsonPath::GetInstance()
    {
        if (!JsonPath::IsInitialized()) {
            JsonPath::Initialize();
        }
        return *JsonPath::parser;
    }

    JsonPath::JsonPath(const std::string& path)
        : path(path)
    {
        if (!GetInstance().parse(path, parsedPath)) {
            throw std::logic_error("JsonPath parser failed to parse the given path.");
        }
    }

    JsonPath::JsonPath(const JsonPath& jsonPath)
        : JsonPath(jsonPath.getPath())
    {}

    Poco::Dynamic::Var JsonPath::query(Poco::Dynamic::Var& values) const
    {
        JsonPathScope scope{values, values};
        return parsedPath(scope);
    }

    Poco::Dynamic::Var JsonPath::queryConst(const Poco::Dynamic::Var& values) const
    {
        Poco::Dynamic::Var clonedValues = Helpers::JsonHelper::clone(values);
        return query(clonedValues);
    }

    const std::string& JsonPath::getPath() const
    {
        return path;
    }

    bool JsonPath::hasOperator(const std::string& symbol) const
    {
        return this->operators.find(symbol) != this->operators.end();
    }

    const std::shared_ptr<Operators::IOperator> JsonPath::getOperator(const std::string& symbol) const
    {
        if (hasOperator(symbol)) {
            return operators.find(symbol)->second;
        } else {
            return nullptr;
        }
    }
}