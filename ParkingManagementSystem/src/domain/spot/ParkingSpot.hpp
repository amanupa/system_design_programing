#pragma once

#include <memory>
#include <string>

#include "common/enums/SpotType.hpp"
#include "common/enums/VehicleSize.hpp"
#include "domain/vehicle/Vehicle.hpp"

namespace pms {

/**
 * @class ParkingSpot
 * @brief Domain entity for a single physical parking spot.
 *
 * Responsibilities:
 *   - Hold its identity (id, floor) and physical traits (type, capacity, charging).
 *   - Answer PHYSICAL compatibility via canFit() — never business policy.
 *   - Guard its own occupancy invariant (assign/release).
 *
 * What it deliberately does NOT do:
 *   - Decide *whether a vehicle should* park here (waste avoidance, VIP access,
 *     EV steering). That is allocation policy and lives in a Strategy (Phase 4).
 *
 * Ownership:
 *   While occupied, the spot co-owns the parked vehicle via
 *   shared_ptr<const Vehicle> (the Ticket will share it too). `const` because a
 *   spot observes its occupant, it never mutates it.
 *
 * SOLID:
 *   - SRP : models one spot + its occupancy invariant.
 *   - OCP : new spot kinds are new subclasses (presets / overridden canFit).
 *   - LSP : every subtype honours the canFit/assign contract.
 *   - DIP : depends on the Vehicle abstraction, not concrete vehicles.
 */
class ParkingSpot {
public:
    virtual ~ParkingSpot() = default;

    ParkingSpot(const ParkingSpot&) = delete;
    ParkingSpot& operator=(const ParkingSpot&) = delete;

    const std::string& id() const noexcept { return id_; }
    int floorNumber() const noexcept { return floorNumber_; }
    SpotType type() const noexcept { return type_; }
    VehicleSize capacity() const noexcept { return capacity_; }
    bool hasCharging() const noexcept { return hasCharging_; }

    bool isOccupied() const noexcept { return occupied_; }

    /// Non-owning view of the current occupant (nullptr if free).
    const Vehicle* parkedVehicle() const noexcept { return vehicle_.get(); }

    /**
     * Physical compatibility: can this vehicle fit here at all?
     * Virtual so an exotic spot kind can refine the rule; the default is
     * size-fits + charging-need-satisfied. Occupancy is NOT considered here.
     */
    virtual bool canFit(const Vehicle& vehicle) const noexcept;

    /**
     * Park a vehicle here.
     * @throws InvalidArgumentException  if vehicle is null.
     * @throws SpotUnavailableException  if occupied or the vehicle cannot fit.
     */
    void assign(std::shared_ptr<const Vehicle> vehicle);

    /**
     * Free the spot and hand back its occupant (e.g. for history archival).
     * @throws SpotUnavailableException if the spot is already free.
     */
    std::shared_ptr<const Vehicle> release();

protected:
    ParkingSpot(std::string id, int floorNumber, SpotType type,
                VehicleSize capacity, bool hasCharging);

private:
    std::string id_;
    int floorNumber_;
    SpotType type_;
    VehicleSize capacity_;
    bool hasCharging_;
    bool occupied_ = false;
    std::shared_ptr<const Vehicle> vehicle_;
};

}  // namespace pms
