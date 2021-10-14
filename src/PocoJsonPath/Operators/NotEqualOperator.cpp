//
// Created by desrumaux on 14/10/2021.
//

#include "NotEqualOperator.hpp"

namespace PocoJsonPath {
    namespace Operators {

        /***
         * Invoke an operator
         *
         * @param scope
         * @param leftMember
         * @param rightMember
         *
         * @return result
         */
        Poco::Dynamic::Var NotEqualOperator::invoke(const JsonPathScope& scope, Poco::Dynamic::Var& leftMember, Poco::Dynamic::Var& rightMember) const
        {
            auto var = EqualOperator::invoke(scope, leftMember, rightMember);
            if (var.isBoolean()) {
                return Poco::Dynamic::Var{!var.extract<bool>()};
            }
            return var;
        }

    }
}