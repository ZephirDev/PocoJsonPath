//
// Created by desrumaux on 11/10/2021.
//

#ifndef POCOJSONPATH_ADDOPERATOR_HPP
#define POCOJSONPATH_ADDOPERATOR_HPP

#include "AbstractOperator.hpp"

namespace PocoJsonPath {
    namespace Operators {

        class AddOperator : public AbstractOperator {
        public:

            /***
             * Invoke an operator on string
             *
             * @param scope
             * @param leftMember
             * @param rightMember
             *
             * @return result
             */
            virtual Poco::Dynamic::Var invokeString(const JsonPathScope& scope, std::string& leftMember, std::string& rightMember) const;

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

#endif //POCOJSONPATH_ADDOPERATOR_HPP
