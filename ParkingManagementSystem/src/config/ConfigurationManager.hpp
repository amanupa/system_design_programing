#pragma once

#include "common/logging/ILogger.hpp"
#include "config/IConfigurationSource.hpp"
#include "config/ParkingLotConfig.hpp"

namespace pms {

/**
 * @class ConfigurationManager
 * @brief Single source of truth for the lot configuration.
 *
 * Loads a validated ParkingLotConfig from an injected IConfigurationSource and
 * caches it, so the composition root and every manager read configuration from
 * exactly one place (no duplicated, drifting constants). reload() re-reads the
 * source (e.g. after an admin edits the file).
 *
 * Collaborators (injected): IConfigurationSource&, ILogger&.
 * SOLID: SRP (own the active config), DIP (depends on the source abstraction).
 */
class ConfigurationManager {
public:
    ConfigurationManager(const IConfigurationSource& source, ILogger& logger);

    ConfigurationManager(const ConfigurationManager&) = delete;
    ConfigurationManager& operator=(const ConfigurationManager&) = delete;

    const ParkingLotConfig& config() const noexcept { return config_; }

    /// Re-read the configuration from the source.
    void reload();

private:
    const IConfigurationSource& source_;
    ILogger& logger_;
    ParkingLotConfig config_;
};

}  // namespace pms
