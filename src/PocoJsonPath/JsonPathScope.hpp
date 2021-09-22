//
// Created by desrumaux on 25/08/2021.
//

#ifndef POCOJSONPATH_JSONPATHSCOPE_HPP
#define POCOJSONPATH_JSONPATHSCOPE_HPP

#include <memory>
#include <map>
#include <string>

#include <Poco/Dynamic/Var.h>

#include "Filters/IFilter.hpp"

namespace PocoJsonPath {
    namespace Operators {
        class IOperator;
    }

    class JsonPathScope {
        Poco::Dynamic::Var root;
        Poco::Dynamic::Var current;

        std::map<std::string, std::shared_ptr<Filters::IFilter>> filters;
        std::map<std::string, std::shared_ptr<Operators::IOperator>> operators;

    public:

        JsonPathScope(Poco::Dynamic::Var root, Poco::Dynamic::Var current);

        JsonPathScope(const JsonPathScope& jsonPathScope);

        JsonPathScope(const JsonPathScope& jsonPathScope, Poco::Dynamic::Var current);

        virtual ~JsonPathScope() = default;

        /**
         * @return root
         */
        Poco::Dynamic::Var& getRoot();

        /**
         * @return root
         */
        Poco::Dynamic::Var& getCurrent();

        /**
         * Set the filters
         *
         * @param filters
         *
         * @return self
         */
        JsonPathScope& setFilters(const std::map<std::string, std::shared_ptr<Filters::IFilter>>& filters);

        /**
         * Get the filters
         *
         * @return filters
         */
        const std::map<std::string, std::shared_ptr<Filters::IFilter>>& getFilters() const;

        /**
         * Add a filter
         *
         * @param filterName
         * @param filter
         *
         * @return self
         */
        JsonPathScope& addFilter(const std::string& filterName, std::shared_ptr<Filters::IFilter> filter);

        /**
         * Remove a filter
         *
         * @param filter
         *
         * @return self
         */
        JsonPathScope& removeFilter(const std::string& filter);

        /**
         * Get the filter
         *
         * @param filter
         *
         * @return filter or nullptr
         */
        std::shared_ptr<Filters::IFilter> getFilter(const std::string& filter) const;

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
        Poco::Dynamic::Var invokeFilter(const std::string& filterName, std::vector<Poco::Dynamic::Var>& parameters) const;

        /**
         * Get the operator
         *
         * @param operator
         *
         * @return operator or nullptr
         */
        std::shared_ptr<Operators::IOperator> getOperator(const std::string& operatorName) const;

        /**
         * Invoke an operator
         *
         * @param operatorName
         * @param leftMember
         * @param rightMember
         *
         * @return value
         */
        Poco::Dynamic::Var invokeOperator(const std::string& operatorName, Poco::Dynamic::Var& leftMember, Poco::Dynamic::Var& rightMember) const;
    };

}

#endif //POCOJSONPATH_JSONPATHSCOPE_HPP
