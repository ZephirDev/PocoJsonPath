//
// Created by desrumaux on 14/10/2021.
//

#ifndef POCOJSONPATH_LOWERTHANOPERATOR_HPP
#define POCOJSONPATH_LOWERTHANOPERATOR_HPP

#include "AbstractOperator.hpp"

namespace PocoJsonPath {
    namespace Operators {
        class LowerThanOperator : public AbstractOperator {
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


#endif //POCOJSONPATH_LOWERTHANOPERATOR_HPP
