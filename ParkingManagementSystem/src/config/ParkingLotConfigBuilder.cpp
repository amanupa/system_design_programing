#include "config/ParkingLotConfigBuilder.hpp"

#include <set>
#include <utility>

#include "common/exceptions/ParkingException.hpp"

namespace pms {

ParkingLotConfigBuilder& ParkingLotConfigBuilder::name(std::string name) {
    name_ = std::move(name);
    return *this;
}

ParkingLotConfigBuilder& ParkingLotConfigBuilder::addFloor(
    int floorNumber, std::map<SpotType, int> spotCounts) {
    floors_.push_back(FloorConfig{floorNumber, std::move(spotCounts)});
    return *this;
}

ParkingLotConfigBuilder& ParkingLotConfigBuilder::addGate(std::string id,
                                                          GateType type) {
    gates_.push_back(GateConfig{std::move(id), type});
    return *this;
}

ParkingLotConfigBuilder& ParkingLotConfigBuilder::pricing(PricingConfig pricing) {
    pricing_ = std::move(pricing);
    return *this;
}

ParkingLotConfig ParkingLotConfigBuilder::build() const {
    if (name_.empty()) {
        throw InvalidConfigurationException("Config: lot name must not be empty");
    }

    // --- Floors ---------------------------------------------------------------
    if (floors_.empty()) {
        throw InvalidConfigurationException("Config: at least one floor is required");
    }
    std::set<int> floorNumbers;
    std::size_t totalSpots = 0;
    for (const FloorConfig& floor : floors_) {
        if (!floorNumbers.insert(floor.floorNumber).second) {
            throw InvalidConfigurationException(
                "Config: duplicate floor number " + std::to_string(floor.floorNumber));
        }
        for (const auto& [type, count] : floor.spotCounts) {
            (void)type;
            if (count < 0) {
                throw InvalidConfigurationException(
                    "Config: negative spot count on floor " +
                    std::to_string(floor.floorNumber));
            }
        }
        totalSpots += floor.totalSpots();
    }
    if (totalSpots == 0) {
        throw InvalidConfigurationException("Config: the lot has zero spots");
    }

    // --- Gates ----------------------------------------------------------------
    if (gates_.empty()) {
        throw InvalidConfigurationException("Config: at least one gate is required");
    }
    std::set<std::string> gateIds;
    bool hasEntry = false;
    bool hasExit = false;
    for (const GateConfig& gate : gates_) {
        if (gate.id.empty()) {
            throw InvalidConfigurationException("Config: gate id must not be empty");
        }
        if (!gateIds.insert(gate.id).second) {
            throw InvalidConfigurationException("Config: duplicate gate id " + gate.id);
        }
        if (gate.type == GateType::Entry || gate.type == GateType::EntryExit) {
            hasEntry = true;
        }
        if (gate.type == GateType::Exit || gate.type == GateType::EntryExit) {
            hasExit = true;
        }
    }
    if (!hasEntry) {
        throw InvalidConfigurationException(
            "Config: needs at least one entry-capable gate");
    }
    if (!hasExit) {
        throw InvalidConfigurationException(
            "Config: needs at least one exit-capable gate");
    }

    // --- Pricing --------------------------------------------------------------
    if (pricing_.baseRate <= Money::zero()) {
        throw InvalidConfigurationException("Config: base rate must be positive");
    }
    if ((pricing_.scheme == PricingScheme::Weekend ||
         pricing_.scheme == PricingScheme::Holiday) &&
        pricing_.premiumRate <= Money::zero()) {
        throw InvalidConfigurationException(
            "Config: premium rate must be positive for weekend/holiday pricing");
    }
    if (pricing_.vipDiscountPercent < 0 || pricing_.vipDiscountPercent > 100) {
        throw InvalidConfigurationException(
            "Config: VIP discount percent must be in [0, 100]");
    }
    if (pricing_.electricSurcharge < Money::zero()) {
        throw InvalidConfigurationException(
            "Config: electric surcharge must not be negative");
    }

    return ParkingLotConfig(name_, floors_, gates_, pricing_);
}

}  // namespace pms
