//
// Created by desrumaux on 13/10/2021.
//

#ifndef POCOJSONPATH_MULTOPERATOR_HPP
#define POCOJSONPATH_MULTOPERATOR_HPP

#include "AbstractOperator.hpp"

namespace PocoJsonPath {
    namespace Operators {

        class MultOperator : public AbstractOperator {
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
            virtual Poco::Dynamic::Var invokeStringMult(const JsonPathScope& scope, std::string& leftMember, double& rightMember) const;

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

#endif //POCOJSONPATH_MULTOPERATOR_HPP
