//
// Created by desrumaux on 02/09/2021.
//

#ifndef POCOJSONPATH_IFILTER_HPP
#define POCOJSONPATH_IFILTER_HPP

#include <vector>

#include <Poco/Dynamic/Var.h>

namespace PocoJsonPath {
    namespace Filters {

        class IFilter {
        public:

            /**
             * Filter an subject
             *
             * @param subject
             * @param parameters
             *
             * @return result
             */
            virtual Poco::Dynamic::Var invoke(Poco::Dynamic::Var subject, std::vector<Poco::Dynamic::Var>& parameters) const = 0;

        };

    }
}

#endif //POCOJSONPATH_IFILTER_HPP
