//
// Created by desrumaux on 14/10/2021.
//

#include "OrOperator.hpp"

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
        Poco::Dynamic::Var OrOperator::invoke(const JsonPathScope& scope, Poco::Dynamic::Var& leftMember, Poco::Dynamic::Var& rightMember) const
        {
            bool left = !leftMember.isEmpty();
            if (leftMember.isBoolean()) {
                left = leftMember.extract<bool>();
            }

            if (left) {
                return true;
            }

            bool right = !rightMember.isEmpty();
            if (rightMember.isBoolean()) {
                right = rightMember.extract<bool>();
            }

            return right;
        }

    }
}