#pragma once

#include "Vehicle.hpp"

namespace pms {

/**
 * @class VipVehicle
 * @brief A privileged vehicle entitled to priority allocation and VIP pricing.
 *
 * Overrides isPrivileged(); the allocation Strategy may use this to prefer VIP
 * spots / jump the queue, and the fee Strategy to apply VIP rates.
 *
 * Same orthogonality caveat as ElectricVehicle: "VIP" is a status that could
 * apply to any vehicle. It is a subclass here to satisfy the catalogue spec,
 * but isPrivileged() is the stable seam callers depend on.
 */
class VipVehicle final : public Vehicle {
public:
    explicit VipVehicle(std::string licensePlate)
        : Vehicle(VehicleType::Vip, std::move(licensePlate), VehicleSize::Medium) {}

    bool isPrivileged() const noexcept override { return true; }
};

}  // namespace pms
