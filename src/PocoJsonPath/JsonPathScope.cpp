//
// Created by desrumaux on 02/09/2021.
//


#include "JsonPathScope.hpp"

#include "Operators/IOperator.hpp"
#include "Operators/AddOperator.hpp"
#include "Operators/SubstractOperator.hpp"
#include "Operators/MultOperator.hpp"
#include "Operators/DivOperator.hpp"
#include "Operators/EqualOperator.hpp"
#include "Operators/NotEqualOperator.hpp"
#include "Operators/LowerThanOperator.hpp"
#include "Operators/LowerThanOrEqualOperator.hpp"
#include "Operators/GreaterThanOperator.hpp"
#include "Operators/GreaterThanOrEqualOperator.hpp"
#include "Operators/AndOperator.hpp"
#include "Operators/OrOperator.hpp"

namespace PocoJsonPath {

    JsonPathScope::JsonPathScope(Poco::Dynamic::Var root, Poco::Dynamic::Var current)
        : root(root)
        , current(current)
        , operators({
            {"+", std::make_shared<Operators::AddOperator>()},
            {"-", std::make_shared<Operators::SubstractOperator>()},
            {"*", std::make_shared<Operators::MultOperator>()},
            {"/", std::make_shared<Operators::DivOperator>()},
            {"==", std::make_shared<Operators::EqualOperator>()},
            {"!=", std::make_shared<Operators::NotEqualOperator>()},
            {"<", std::make_shared<Operators::LowerThanOperator>()},
            {"<=", std::make_shared<Operators::LowerThanOrEqualOperator>()},
            {">", std::make_shared<Operators::GreaterThanOperator>()},
            {">=", std::make_shared<Operators::GreaterThanOrEqualOperator>()},
            {"&&", std::make_shared<Operators::AndOperator>()},
            {"||", std::make_shared<Operators::OrOperator>()},
        })
    {
        std::map<std::string, std::vector<std::string>> aliases{
            {"&&", {"and"}},
            {"||", {"or"}},
        };

        for (auto& operatorToAlias : aliases) {
            for (auto& alias : operatorToAlias.second) {
                operators[alias] = operators[operatorToAlias.first];
            }
        }
    }

    JsonPathScope::JsonPathScope(const JsonPathScope& jsonPathScope)
        : root(jsonPathScope.root)
        , current(jsonPathScope.current)
        , filters(jsonPathScope.filters)
        , operators(jsonPathScope.operators)
    {}

    JsonPathScope::JsonPathScope(const JsonPathScope& jsonPathScope, Poco::Dynamic::Var current)
        : root(jsonPathScope.root)
        , current(current)
        , filters(jsonPathScope.filters)
        , operators(jsonPathScope.operators)
    {}

    /**
     * @return root
     */
    Poco::Dynamic::Var& JsonPathScope::getRoot()
    {
        return root;
    }

    /**
     * @return root
     */
    Poco::Dynamic::Var& JsonPathScope::getCurrent()
    {
        return current;
    }

    /**
     * Set the filters
     *
     * @param filters
     *
     * @return self
     */
    JsonPathScope& JsonPathScope::setFilters(const std::map<std::string, std::shared_ptr<Filters::IFilter>>& filters)
    {
        this->filters = filters;
        return *this;
    }

    /**
     * Get the filters
     *
     * @return filters
     */
    const std::map<std::string, std::shared_ptr<Filters::IFilter>>& JsonPathScope::getFilters() const
    {
        return filters;
    }

    /**
     * Add a filter
     *
     * @param filterName
     * @param filter
     *
     * @return self
     */
    JsonPathScope& JsonPathScope::addFilter(const std::string& filterName, std::shared_ptr<Filters::IFilter> filter)
    {
        filters[filterName] = filter;
        return *this;
    }

    /**
     * Remove a filter
     *
     * @param filter
     *
     * @return self
     */
    JsonPathScope& JsonPathScope::removeFilter(const std::string& filter)
    {
        auto it = filters.find(filter);
        if (filters.end() != it) {
            filters.erase(it);
        }
        return *this;
    }

    /**
     * Get the filter
     *
     * @param filter
     *
     * @return filter or nullptr
     */
    std::shared_ptr<Filters::IFilter> JsonPathScope::getFilter(const std::string& filter) const
    {
        auto it = filters.find(filter);
        if (filters.end() != it) {
            return it->second;
        }
        return nullptr;
    }

    /**
     * Invoke a filter
     *
     * @param filterName
     * @param parameters
     *
     * @throw std::logic_error when filter doesn't exists
     *
     * @return result
     */
    Poco::Dynamic::Var JsonPathScope::invokeFilter(const std::string& filterName, std::vector<Poco::Dynamic::Var>& parameters) const
    {
        auto filter = getFilter(filterName);
        if (nullptr == filter) {
            throw std::logic_error("The '" + filterName + "' filter doesn't exists.");
        }
        return filter->invoke(current, parameters);
    }

    /**
     * Get the operator
     *
     * @param operator
     *
     * @return operator or nullptr
     */
    std::shared_ptr<Operators::IOperator> JsonPathScope::getOperator(const std::string& operatorName) const
    {
        auto it = operators.find(operatorName);
        if (operators.end() != it) {
            return it->second;
        }
        return nullptr;
    }

    /**
     * Invoke an operator
     *
     * @param operatorName
     * @param leftMember
     * @param rightMember
     *
     * @return value
     */
    Poco::Dynamic::Var JsonPathScope::invokeOperator(const std::string& operatorName, Poco::Dynamic::Var& leftMember, Poco::Dynamic::Var& rightMember) const
    {
        auto op = getOperator(operatorName);
        if (nullptr == op) {
            throw std::logic_error("The '" + operatorName + "' operator doesn't exists.");
        }
        return op->invoke(*this, leftMember, rightMember);
    }

}