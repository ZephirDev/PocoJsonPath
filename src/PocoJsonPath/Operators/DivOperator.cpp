//
// Created by desrumaux on 13/10/2021.
//

#include "DivOperator.hpp"

#include <Poco/Exception.h>

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
        Poco::Dynamic::Var DivOperator::invokeNumber(const JsonPathScope& scope, double& leftMember, double& rightMember) const
        {
            if (rightMember == 0) {
                throw Poco::DataException{"Error: devide by 0."};
            }

            return Poco::Dynamic::Var{leftMember / rightMember};
        }

    }
}
