//
// Created by desrumaux on 13/10/2021.
//

#include "MultOperator.hpp"

#include "PocoJsonPath/Helpers/JsonHelper.hpp"

namespace PocoJsonPath {
    namespace Operators {

        /***
         * Invoke an operator on number
         *
         * @param scope
         * @param leftMember
         * @param rightMember
         *
         * @return result
         */
        Poco::Dynamic::Var MultOperator::invokeStringMult(const JsonPathScope& scope, std::string& leftMember, double& rightMember) const
        {
            std::string result;
            for (double i = 0; i < rightMember; i++) {
                result += leftMember;
            }
            return Poco::Dynamic::Var{result};
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
        Poco::Dynamic::Var MultOperator::invokeNumber(const JsonPathScope& scope, double& leftMember, double& rightMember) const
        {
            return Poco::Dynamic::Var{leftMember * rightMember};
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
        Poco::Dynamic::Var MultOperator::invoke(const JsonPathScope& scope, Poco::Dynamic::Var& leftMember, Poco::Dynamic::Var& rightMember) const
        {
            if (leftMember.isString() && rightMember.isNumeric()) {
                auto str = leftMember.extract<std::string>();
                auto num = Helpers::JsonHelper::castToDouble(rightMember).value();
                return invokeStringMult(scope, str, num);
            } else if (leftMember.isNumeric() && rightMember.isString()) {
                auto str = rightMember.extract<std::string>();
                auto num = Helpers::JsonHelper::castToDouble(leftMember).value();
                return invokeStringMult(scope, str, num);
            }

            return AbstractOperator::invoke(scope, leftMember, rightMember);
        }

    }
}
