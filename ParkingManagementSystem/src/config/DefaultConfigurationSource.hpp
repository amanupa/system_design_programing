#pragma once

#include "config/IConfigurationSource.hpp"

namespace pms {

/**
 * @class DefaultConfigurationSource
 * @brief Built-in source producing a sensible multi-floor lot.
 *
 * The reference configuration used by tests and the default runtime. Swapping in
 * a FileConfigurationSource later changes only which source the composition root
 * constructs — ConfigurationManager and everything downstream are untouched.
 */
class DefaultConfigurationSource : public IConfigurationSource {
public:
    ParkingLotConfig load() const override;
};

}  // namespace pms
