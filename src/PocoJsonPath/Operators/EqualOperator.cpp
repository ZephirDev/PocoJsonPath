//
// Created by desrumaux on 14/10/2021.
//

#include "EqualOperator.hpp"

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
        Poco::Dynamic::Var EqualOperator::invokeString(const JsonPathScope& scope, std::string& leftMember, std::string& rightMember) const
        {
            return Poco::Dynamic::Var{leftMember == rightMember};
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
        Poco::Dynamic::Var EqualOperator::invokeNumber(const JsonPathScope& scope, double& leftMember, double& rightMember) const
        {
            return Poco::Dynamic::Var{leftMember == rightMember};
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
        Poco::Dynamic::Var EqualOperator::invokeBoolean(const JsonPathScope& scope, bool& leftMember, bool& rightMember) const
        {
            return Poco::Dynamic::Var{leftMember == rightMember};
        }

    }
}
