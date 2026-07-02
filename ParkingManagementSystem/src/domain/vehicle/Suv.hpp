#pragma once

#include "Vehicle.hpp"

namespace pms {

/// A sport-utility vehicle. Large footprint (needs a Large/Truck-class spot).
class Suv final : public Vehicle {
public:
    explicit Suv(std::string licensePlate)
        : Vehicle(VehicleType::Suv, std::move(licensePlate), VehicleSize::Large) {}
};

}  // namespace pms
