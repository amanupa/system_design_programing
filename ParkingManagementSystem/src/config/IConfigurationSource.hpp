#pragma once

#include "config/ParkingLotConfig.hpp"

namespace pms {

/**
 * @class IConfigurationSource
 * @brief Where a ParkingLotConfig comes from.
 *
 * Abstracts the origin (hard-coded default now; a JSON/YAML file or remote
 * service later) so the rest of the system depends only on "give me a validated
 * config", never on how it is loaded (DIP). New sources are new classes (OCP).
 */
class IConfigurationSource {
public:
    virtual ~IConfigurationSource() = default;

    /// @throws InvalidConfigurationException if the source yields an invalid config.
    virtual ParkingLotConfig load() const = 0;
};

}  // namespace pms
