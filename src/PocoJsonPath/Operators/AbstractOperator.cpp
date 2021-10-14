//
// Created by desrumaux on 22/09/2021.
//

#include "AbstractOperator.hpp"

#include "PocoJsonPath/Helpers/JsonHelper.hpp"

namespace PocoJsonPath {
    namespace Operators {

        /***
         * Invoke an operator on string
         *
         * @param scope
         * @param leftMember
         * @param rightMember
         *
         * @return result
         */
        Poco::Dynamic::Var AbstractOperator::invokeString(const JsonPathScope& scope, std::string& leftMember, std::string& rightMember) const
        {
            return Poco::Dynamic::Var{};
        }

        /***
         * Invoke an operator on number
         *
         * @param scope
         * @param leftMember
         * @param rightMember
         *
         * @return result
         */
        Poco::Dynamic::Var AbstractOperator::invokeNumber(const JsonPathScope& scope, double& leftMember, double& rightMember) const
        {
            return Poco::Dynamic::Var{};
        }

        /***
         * Invoke an operator on boolean
         *
         * @param scope
         * @param leftMember
         * @param rightMember
         *
         * @return result
         */
        Poco::Dynamic::Var AbstractOperator::invokeBoolean(const JsonPathScope& scope, bool& leftMember, bool& rightMember) const
        {
            return Poco::Dynamic::Var{};
        }

        /***
         * Invoke an operator on object
         *
         * @param scope
         * @param leftMember
         * @param rightMember
         *
         * @return result
         */
        Poco::Dynamic::Var AbstractOperator::invokeObject(const JsonPathScope& scope, Poco::JSON::Object::Ptr& leftMember, Poco::JSON::Object::Ptr& rightMember) const
        {
            return Poco::Dynamic::Var{};
        }

        /***
         * Invoke an operator on object
         *
         * @param scope
         * @param leftMember
         * @param rightMember
         *
         * @return result
         */
        Poco::Dynamic::Var AbstractOperator::invokeArray(const JsonPathScope& scope, Poco::JSON::Array::Ptr& leftMember, Poco::JSON::Array::Ptr& rightMember) const
        {
            return Poco::Dynamic::Var{};
        }

        /***
         * Invoke an operator
         *
         * @param scope
         * @param leftMember
         * @param rightMember
         *
         * @return result
         */
        Poco::Dynamic::Var AbstractOperator::invoke(const JsonPathScope& scope, Poco::Dynamic::Var& leftMember, Poco::Dynamic::Var& rightMember) const
        {
            auto objLeftMember = Helpers::JsonHelper::castToJsonObject(leftMember);
            auto objRightMember = Helpers::JsonHelper::castToJsonObject(rightMember);
            if (objLeftMember.has_value() && objRightMember.has_value()) {
                return invokeObject(scope, objLeftMember.value(), objRightMember.value());
            }

            auto arrLeftMember = Helpers::JsonHelper::castToJsonArray(leftMember);
            auto arrRightMember = Helpers::JsonHelper::castToJsonArray(rightMember);
            if (arrLeftMember.has_value() && arrRightMember.has_value()) {
                return invokeArray(scope, arrLeftMember.value(), arrRightMember.value());
            }

            if (leftMember.isString() && rightMember.isString()) {
                auto strLeftMember = leftMember.extract<std::string>();
                auto strRightMember = rightMember.extract<std::string>();
                return invokeString(scope, strLeftMember, strRightMember);
            }

            if (leftMember.isBoolean() && rightMember.isBoolean()) {
                auto boolLeftMember = leftMember.extract<bool>();
                auto boolRightMember = rightMember.extract<bool>();
                return invokeBoolean(scope, boolLeftMember, boolRightMember);
            }

            auto nbLeftMember = Helpers::JsonHelper::castToDouble(leftMember);
            auto nbRightMember = Helpers::JsonHelper::castToDouble(rightMember);
            if (nbLeftMember.has_value() && nbRightMember.has_value()) {
                return invokeNumber(scope, nbLeftMember.value(), nbRightMember.value());
            }

            return Poco::Dynamic::Var{};
        }

    }
}
