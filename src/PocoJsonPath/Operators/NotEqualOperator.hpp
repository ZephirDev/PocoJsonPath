//
// Created by desrumaux on 14/10/2021.
//

#ifndef POCOJSONPATH_NOTEQUALOPERATOR_HPP
#define POCOJSONPATH_NOTEQUALOPERATOR_HPP

#include "EqualOperator.hpp"

namespace PocoJsonPath {
    namespace Operators {

        class NotEqualOperator : public EqualOperator {
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


#endif //POCOJSONPATH_NOTEQUALOPERATOR_HPP
