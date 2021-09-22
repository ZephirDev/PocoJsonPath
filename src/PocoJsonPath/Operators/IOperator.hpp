//
// Created by desrumaux on 18/09/2021.
//

#ifndef POCOJSONPATH_IOPERATOR_HPP
#define POCOJSONPATH_IOPERATOR_HPP

#include "PocoJsonPath/JsonPathScope.hpp"

namespace PocoJsonPath {
    namespace Operators {
        class IOperator {
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
            virtual Poco::Dynamic::Var invoke(const JsonPathScope& scope, Poco::Dynamic::Var& leftMember, Poco::Dynamic::Var& rightMember) const = 0;
        };
    }
}

#endif //POCOJSONPATH_IOPERATOR_HPP
