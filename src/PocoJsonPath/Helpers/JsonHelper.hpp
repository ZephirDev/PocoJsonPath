//
// Created by desrumaux on 25/08/2021.
//

#ifndef POCOJSONPATH_JSONHELPER_HPP
#define POCOJSONPATH_JSONHELPER_HPP

#include <optional>

#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Array.h>


namespace PocoJsonPath {
    namespace Helpers {

        namespace JsonHelper {

            /**
             * Clone the json object.
             *
             * @param json
             *
             * @return json
             */
            Poco::Dynamic::Var clone(const Poco::Dynamic::Var& json);

            /**
             * Try cast to a json object
             *
             * @param json
             *
             * @return mb json object
             */
            std::optional<Poco::JSON::Object::Ptr> castToJsonObject(Poco::Dynamic::Var& json) noexcept;

            /**
             * Try cast to a json array
             *
             * @param json
             *
             * @return mb json array
             */
            std::optional<Poco::JSON::Array::Ptr> castToJsonArray(Poco::Dynamic::Var& json) noexcept;

            /**
             * Try cast to a number
             *
             * @param json
             *
             * @return mb json number
             */
            template<typename Result, typename Item, typename... Items>
            inline std::optional<Result> castToNumber(Poco::Dynamic::Var& json) noexcept
            {
                try {
                    return Result{json.extract<Item>()};
                } catch (const std::exception&) {
                    if constexpr (sizeof...(Items) > 0) {
                        return castToNumber<Result, Items...>(json);
                    } else {
                        return std::nullopt;
                    }
                }
            }

            /**
             * Try cast to a number
             *
             * @param json
             *
             * @return mb json number
             */
            std::optional<double> castToDouble(Poco::Dynamic::Var& json) noexcept;
        }

    }
}


#endif //POCOJSONPATH_JSONHELPER_HPP
