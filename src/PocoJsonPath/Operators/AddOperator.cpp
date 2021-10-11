//
// Created by desrumaux on 11/10/2021.
//

#include "AddOperator.hpp"

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
        Poco::Dynamic::Var AddOperator::invokeString(const JsonPathScope& scope, std::string& leftMember, std::string& rightMember) const
        {
            return Poco::Dynamic::Var{leftMember + rightMember};
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
        Poco::Dynamic::Var AddOperator::invokeNumber(const JsonPathScope& scope, double& leftMember, double& rightMember) const
        {
            return Poco::Dynamic::Var{leftMember + rightMember};
        }

    }
}