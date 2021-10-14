//
// Created by desrumaux on 14/10/2021.
//

#ifndef POCOJSONPATH_GREATERTHANOREQUALOPERATOR_HPP
#define POCOJSONPATH_GREATERTHANOREQUALOPERATOR_HPP

#include "AbstractOperator.hpp"

namespace PocoJsonPath {
    namespace Operators {
        class GreaterThanOrEqualOperator : public AbstractOperator {
        public:

            /***
             * Invoke an operator on number
             *
             * @param scope
             * @param leftMember
             * @param rightMember
             *
             * @return result
             */
            virtual Poco::Dynamic::Var invokeNumber(const JsonPathScope& scope, double& leftMember, double& rightMember) const;
        };
    }
}

#endif //POCOJSONPATH_GREATERTHANOREQUALOPERATOR_HPP
