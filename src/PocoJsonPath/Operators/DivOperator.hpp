//
// Created by desrumaux on 13/10/2021.
//

#ifndef POCOJSONPATH_DIVOPERATOR_HPP
#define POCOJSONPATH_DIVOPERATOR_HPP

#include "AbstractOperator.hpp"

namespace PocoJsonPath {
    namespace Operators {

        class DivOperator : public AbstractOperator {
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

#endif //POCOJSONPATH_DIVOPERATOR_HPP
