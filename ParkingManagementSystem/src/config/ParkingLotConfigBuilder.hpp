#pragma once

#include <map>
#include <string>
#include <vector>

#include "config/ConfigTypes.hpp"
#include "config/ParkingLotConfig.hpp"

namespace pms {

/**
 * @class ParkingLotConfigBuilder
 * @brief Fluent builder that assembles and validates a ParkingLotConfig.
 *
 * Pattern: Builder. The configuration has many parts (floors with spot maps,
 * gates, pricing) added incrementally; build() validates the assembled whole in
 * one place and is the only way to obtain a ParkingLotConfig.
 *
 * Cross-field validation (e.g. "needs both an entry-capable and an exit-capable
 * gate") can only be done once everything is present — exactly what a Builder's
 * terminal build() step is for.
 */
class ParkingLotConfigBuilder {
public:
    ParkingLotConfigBuilder& name(std::string name);
    ParkingLotConfigBuilder& addFloor(int floorNumber,
                                      std::map<SpotType, int> spotCounts);
    ParkingLotConfigBuilder& addGate(std::string id, GateType type);
    ParkingLotConfigBuilder& pricing(PricingConfig pricing);

    /// @throws InvalidConfigurationException if the assembled config is invalid.
    ParkingLotConfig build() const;

private:
    std::string name_ = "Parking Lot";
    std::vector<FloorConfig> floors_;
    std::vector<GateConfig> gates_;
    PricingConfig pricing_{};
};

}  // namespace pms
