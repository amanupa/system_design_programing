#pragma once

#include "Vehicle.hpp"

namespace pms {

/// A standard passenger car. Medium footprint; no special capabilities.
class Car final : public Vehicle {
public:
    explicit Car(std::string licensePlate)
        : Vehicle(VehicleType::Car, std::move(licensePlate), VehicleSize::Medium) {}
};

}  // namespace pms
