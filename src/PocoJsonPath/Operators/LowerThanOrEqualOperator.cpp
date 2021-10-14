//
// Created by desrumaux on 14/10/2021.
//

#include "LowerThanOrEqualOperator.hpp"

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
        Poco::Dynamic::Var LowerThanOrEqualOperator::invokeNumber(const JsonPathScope& scope, double& leftMember, double& rightMember) const
        {
            return Poco::Dynamic::Var{leftMember <= rightMember};
        }

    }
}
