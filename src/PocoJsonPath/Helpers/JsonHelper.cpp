//
// Created by desrumaux on 25/08/2021.
//

#include "JsonHelper.hpp"

#include <sstream>

#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Stringifier.h>

namespace PocoJsonPath {
    namespace Helpers {

        /**
         * Clone the json object.
         *
         * @param json
         *
         * @return json
         */
        Poco::Dynamic::Var JsonHelper::clone(const Poco::Dynamic::Var& json)
        {
            std::ostringstream oss;
            Poco::JSON::Stringifier::stringify(json, oss);
            Poco::JSON::Parser parser;
            return parser.parse(oss.str());
        }

        /**
         * Try cast to a json object
         *
         * @param json
         *
         * @return mb json object
         */
        std::optional<Poco::JSON::Object::Ptr> JsonHelper::castToJsonObject(Poco::Dynamic::Var& json) noexcept
        {
            try {
                return json.extract<Poco::JSON::Object::Ptr>();
            } catch (const std::exception&) {
                return std::nullopt;
            }
        }

        /**
         * Try cast to a json array
         *
         * @param json
         *
         * @return mb json array
         */
        std::optional<Poco::JSON::Array::Ptr> JsonHelper::castToJsonArray(Poco::Dynamic::Var& json) noexcept
        {
            try {
                return json.extract<Poco::JSON::Array::Ptr>();
            } catch (const std::exception&) {
                return std::nullopt;
            }
        }

        /**
         * Try cast to a number
         *
         * @param json
         *
         * @return mb json number
         */
        std::optional<double> JsonHelper::castToDouble(Poco::Dynamic::Var& json) noexcept
        {
            return JsonHelper::castToNumber<double, double, float, long long, long, int, short>(json);
        }
    }
}
