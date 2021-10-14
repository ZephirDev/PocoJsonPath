//
// Created by desrumaux on 14/10/2021.
//

#ifndef POCOJSONPATH_EQUALOPERATOR_HPP
#define POCOJSONPATH_EQUALOPERATOR_HPP

#include "AbstractOperator.hpp"

namespace PocoJsonPath {
    namespace Operators {
        class EqualOperator : public AbstractOperator {
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

            /***
             * Invoke an operator on boolean
             *
             * @param scope
             * @param leftMember
             * @param rightMember
             *
             * @return result
             */
            virtual Poco::Dynamic::Var invokeBoolean(const JsonPathScope& scope, bool& leftMember, bool& rightMember) const;
        };
    }
}


#endif //POCOJSONPATH_EQUALOPERATOR_HPP
