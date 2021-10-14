//
// Created by desrumaux on 14/10/2021.
//

#ifndef POCOJSONPATH_OROPERATOR_HPP
#define POCOJSONPATH_OROPERATOR_HPP

#include "IOperator.hpp"

namespace PocoJsonPath {
    namespace Operators {
        class OrOperator : public IOperator {
        public:

            /***
             * Invoke an operator
             *
             * @param scope
             * @param leftMember
             * @param rightMember
             *
             * @return result
             */
            virtual Poco::Dynamic::Var invoke(const JsonPathScope& scope, Poco::Dynamic::Var& leftMember, Poco::Dynamic::Var& rightMember) const;
        };
    }
}


#endif //POCOJSONPATH_OROPERATOR_HPP
