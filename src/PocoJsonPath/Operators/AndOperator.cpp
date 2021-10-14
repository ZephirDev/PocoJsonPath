//
// Created by desrumaux on 14/10/2021.
//

#include "AndOperator.hpp"

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
        Poco::Dynamic::Var AndOperator::invoke(const JsonPathScope& scope, Poco::Dynamic::Var& leftMember, Poco::Dynamic::Var& rightMember) const
        {
            if (leftMember.isEmpty() || rightMember.isEmpty()) {
                return false;
            }

            bool left = true;
            if (leftMember.isBoolean()) {
                left = leftMember.extract<bool>();
            }

            if (!left) {
                return false;
            }

            bool right = true;
            if (rightMember.isBoolean()) {
                right = rightMember.extract<bool>();
            }

            return right;
        }

    }
}
