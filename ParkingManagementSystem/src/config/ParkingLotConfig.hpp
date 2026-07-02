#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "config/ConfigTypes.hpp"

namespace pms {

class ParkingLotConfigBuilder;

/**
 * @class ParkingLotConfig
 * @brief Immutable, validated description of an entire parking lot.
 *
 * The single artefact every other layer is built from (Phase 12). Constructed
 * only by ParkingLotConfigBuilder (friend + private ctor), so a config that
 * exists is guaranteed to have passed validation — there is no way to hold a
 * half-specified or contradictory lot definition.
 *
 * SOLID: SRP (it is just the validated configuration data).
 */
class ParkingLotConfig {
public:
    const std::string& name() const noexcept { return name_; }
    const std::vector<FloorConfig>& floors() const noexcept { return floors_; }
    const std::vector<GateConfig>& gates() const noexcept { return gates_; }
    const PricingConfig& pricing() const noexcept { return pricing_; }

    std::size_t floorCount() const noexcept { return floors_.size(); }
    std::size_t gateCount() const noexcept { return gates_.size(); }
    std::size_t totalConfiguredSpots() const;

private:
    friend class ParkingLotConfigBuilder;
    ParkingLotConfig(std::string name, std::vector<FloorConfig> floors,
                     std::vector<GateConfig> gates, PricingConfig pricing);

    std::string name_;
    std::vector<FloorConfig> floors_;
    std::vector<GateConfig> gates_;
    PricingConfig pricing_;
};

}  // namespace pms
