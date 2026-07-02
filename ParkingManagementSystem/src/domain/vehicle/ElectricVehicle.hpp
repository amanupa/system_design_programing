#pragma once

#include "Vehicle.hpp"

namespace pms {

/**
 * @class ElectricVehicle
 * @brief A vehicle that needs a charging-capable spot.
 *
 * Modelled here as an electric *car* (Medium) for the default catalogue. It
 * overrides exactly one behaviour — requiresCharging() — which the allocation
 * Strategy and the fee Strategy consult polymorphically.
 *
 * Design note (composition vs. inheritance):
 *   "Electric" is really an orthogonal capability — an electric truck or an
 *   electric VIP car are both valid. A fully composition-based model would make
 *   `electric` a flag on any Vehicle rather than a subclass, avoiding a
 *   `VipElectricSuv` explosion. The base already exposes requiresCharging() as a
 *   virtual hook, so migrating to that model later does not break callers.
 */
class ElectricVehicle final : public Vehicle {
public:
    explicit ElectricVehicle(std::string licensePlate)
        : Vehicle(VehicleType::ElectricVehicle, std::move(licensePlate),
                  VehicleSize::Medium) {}

    bool requiresCharging() const noexcept override { return true; }
};

}  // namespace pms
