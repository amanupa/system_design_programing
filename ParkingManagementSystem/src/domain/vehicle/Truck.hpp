#pragma once

#include "Vehicle.hpp"

namespace pms {

/// A truck/van. Large footprint; typically restricted to truck-class spots.
class Truck final : public Vehicle {
public:
    explicit Truck(std::string licensePlate)
        : Vehicle(VehicleType::Truck, std::move(licensePlate), VehicleSize::Large) {}
};

}  // namespace pms
