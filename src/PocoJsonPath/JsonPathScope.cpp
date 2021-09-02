//
// Created by desrumaux on 02/09/2021.
//

#include "JsonPathScope.hpp"

namespace PocoJsonPath {

    JsonPathScope::JsonPathScope(Poco::Dynamic::Var root, Poco::Dynamic::Var current)
        : root(root)
        , current(current)
    {}

    JsonPathScope::JsonPathScope(const JsonPathScope& jsonPathScope)
        : root(jsonPathScope.root)
        , current(jsonPathScope.current)
        , filters(jsonPathScope.filters)
    {}

    JsonPathScope::JsonPathScope(const JsonPathScope& jsonPathScope, Poco::Dynamic::Var current)
        : root(jsonPathScope.root)
        , current(current)
        , filters(jsonPathScope.filters)
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

}