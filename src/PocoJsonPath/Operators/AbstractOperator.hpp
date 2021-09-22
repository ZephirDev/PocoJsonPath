//
// Created by desrumaux on 22/09/2021.
//

#ifndef POCOJSONPATH_ABSTRACTOPERATOR_HPP
#define POCOJSONPATH_ABSTRACTOPERATOR_HPP

#include <Poco/JSON/Object.h>
#include <Poco/JSON/Array.h>

#include "IOperator.hpp"

namespace PocoJsonPath {
    namespace Operators {
        class AbstractOperator : public IOperator {
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

            /***
             * Invoke an operator on object
             *
             * @param scope
             * @param leftMember
             * @param rightMember
             *
             * @return result
             */
            virtual Poco::Dynamic::Var invokeObject(const JsonPathScope& scope, Poco::JSON::Object::Ptr& leftMember, Poco::JSON::Object::Ptr& rightMember) const;

            /***
             * Invoke an operator on object
             *
             * @param scope
             * @param leftMember
             * @param rightMember
             *
             * @return result
             */
            virtual Poco::Dynamic::Var invokeArray(const JsonPathScope& scope, Poco::JSON::Array::Ptr& leftMember, Poco::JSON::Array::Ptr& rightMember) const;

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


#endif //POCOJSONPATH_ABSTRACTOPERATOR_HPP
