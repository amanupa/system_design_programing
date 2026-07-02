#pragma once

#include "Vehicle.hpp"

namespace pms {

/// A two-wheeler. Smallest footprint; no special capabilities.
class Bike final : public Vehicle {
public:
    explicit Bike(std::string licensePlate)
        : Vehicle(VehicleType::Bike, std::move(licensePlate), VehicleSize::Small) {}
};

}  // namespace pms
