#include "config/ParkingLotConfig.hpp"

#include <utility>

namespace pms {

ParkingLotConfig::ParkingLotConfig(std::string name,
                                   std::vector<FloorConfig> floors,
                                   std::vector<GateConfig> gates,
                                   PricingConfig pricing)
    : name_(std::move(name)),
      floors_(std::move(floors)),
      gates_(std::move(gates)),
      pricing_(std::move(pricing)) {}

std::size_t ParkingLotConfig::totalConfiguredSpots() const {
    std::size_t total = 0;
    for (const FloorConfig& floor : floors_) {
        total += floor.totalSpots();
    }
    return total;
}

}  // namespace pms
