//
// Created by desrumaux on 25/08/2021.
//

#ifndef POCOJSONPATH_JSONPATH_HPP
#define POCOJSONPATH_JSONPATH_HPP

#include <memory>

#include <Poco/Dynamic/Var.h>
#include <peglib.h>

#include "JsonPathScope.hpp"

namespace PocoJsonPath {
    namespace Operators {
        class IOperator;
    }

    class JsonPath {
        static std::unique_ptr<peg::parser> parser;
        using PathFunction = std::function<Poco::Dynamic::Var(JsonPathScope&)>;
        using OperatorFunction = std::function<Poco::Dynamic::Var(JsonPathScope&, Poco::Dynamic::Var&, Poco::Dynamic::Var&)>;
    public:

        static void Initialize();

        static bool IsInitialized();

        static peg::parser& GetInstance();

    private:

        std::string path;
        PathFunction parsedPath;

        std::map<std::string, std::shared_ptr<Operators::IOperator>> operators;

    public:

        JsonPath(const std::string& path);

        JsonPath(const JsonPath& jsonPath);

        Poco::Dynamic::Var query(Poco::Dynamic::Var& values) const;

        Poco::Dynamic::Var queryConst(const Poco::Dynamic::Var& values) const;

        const std::string& getPath() const;

        bool hasOperator(const std::string& symbol) const;

        const std::shared_ptr<Operators::IOperator> getOperator(const std::string& symbol) const;
    };
}


#endif //POCOJSONPATH_JSONPATH_HPP
