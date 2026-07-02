#pragma once

#include <string>
#include <utility>

#include "common/enums/VehicleSize.hpp"
#include "common/enums/VehicleType.hpp"
#include "common/exceptions/ParkingException.hpp"

namespace pms {

/**
 * @class Vehicle
 * @brief Domain entity for a vehicle that wants to park.
 *
 * Purpose:
 *   Model the intrinsic, real-world properties of a vehicle — and ONLY those.
 *   It answers "what am I?" (type, plate, size, capabilities). It deliberately
 *   does NOT answer "where may I park?" — that is allocation policy and lives in
 *   a Strategy (Phase 4). This keeps the entity stable while policy evolves.
 *
 * Why a base class (and not just one Vehicle + enum):
 *   The base exposes virtual capability queries with safe defaults; subtypes
 *   override only the ones that genuinely differ (an ElectricVehicle needs
 *   charging; a VipVehicle is privileged). Callers depend on these queries, not
 *   on the concrete type — so allocation/fee code works for vehicle types that
 *   don't exist yet (OCP).
 *
 * Construction:
 *   The constructor is `protected` so a bare `Vehicle` cannot be created — you
 *   must go through a concrete subtype (or the VehicleFactory). This enforces
 *   the taxonomy without needing a token pure-virtual.
 *
 * SOLID:
 *   - SRP   : holds vehicle identity/properties only.
 *   - OCP   : new vehicle types add subclasses; existing code is untouched.
 *   - LSP   : every subtype is a fully valid Vehicle (defaults stay sane).
 *   - DIP   : higher layers depend on this abstraction.
 *
 * Identity: a vehicle is identified by its (unique) license plate — a natural
 * key — so no generated id is needed here.
 */
class Vehicle {
public:
    virtual ~Vehicle() = default;

    // Non-copyable: a Vehicle is an entity with identity, not a value to clone.
    Vehicle(const Vehicle&) = delete;
    Vehicle& operator=(const Vehicle&) = delete;

    VehicleType type() const noexcept { return type_; }
    const std::string& licensePlate() const noexcept { return plate_; }
    VehicleSize size() const noexcept { return size_; }

    /// Does this vehicle need a charging-capable spot? Default: no.
    virtual bool requiresCharging() const noexcept { return false; }

    /// Is this vehicle entitled to priority allocation / VIP pricing? Default: no.
    virtual bool isPrivileged() const noexcept { return false; }

protected:
    Vehicle(VehicleType type, std::string licensePlate, VehicleSize size)
        : type_(type), plate_(std::move(licensePlate)), size_(size) {
        if (plate_.empty()) {
            throw InvalidArgumentException("Vehicle: license plate must not be empty");
        }
    }

private:
    VehicleType type_;
    std::string plate_;
    VehicleSize size_;
};

}  // namespace pms
