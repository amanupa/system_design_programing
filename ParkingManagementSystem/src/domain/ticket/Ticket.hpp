#pragma once

#include <memory>
#include <optional>
#include <string>

#include "common/enums/TicketStatus.hpp"
#include "common/util/Time.hpp"
#include "domain/vehicle/Vehicle.hpp"

namespace pms {

class TicketBuilder;  // the sole constructor of Ticket (see below)

/**
 * @class Ticket
 * @brief Record of one parking session (entity, identified by ticket id).
 *
 * Construction:
 *   The constructor is private; only TicketBuilder (a friend) can build one,
 *   and only after validating every required field. This makes a half-built or
 *   inconsistent ticket unrepresentable.
 *
 * Lifecycle:
 *   Created Active with immutable entry data; transitions to Closed exactly once
 *   via close(), which records exit time + gate. Creation fields have no setters
 *   — controlled mutation, not open mutability.
 *
 * Ownership: co-owns the vehicle via shared_ptr<const Vehicle> (the occupied
 * spot shares the same instance), so a ticket remains valid for history even
 * after the spot is freed.
 *
 * SOLID: SRP (it is just the session record + its state machine), DIP (depends
 * on the Vehicle abstraction).
 */
class Ticket {
public:
    const std::string& id() const noexcept { return id_; }
    const Vehicle& vehicle() const noexcept { return *vehicle_; }
    std::shared_ptr<const Vehicle> vehiclePtr() const noexcept { return vehicle_; }
    const std::string& spotId() const noexcept { return spotId_; }
    int floorNumber() const noexcept { return floorNumber_; }
    const std::string& entryGateId() const noexcept { return entryGateId_; }
    TimePoint entryTime() const noexcept { return entryTime_; }

    TicketStatus status() const noexcept { return status_; }
    bool isActive() const noexcept { return status_ == TicketStatus::Active; }
    bool isClosed() const noexcept { return status_ == TicketStatus::Closed; }

    const std::optional<TimePoint>& exitTime() const noexcept { return exitTime_; }
    const std::optional<std::string>& exitGateId() const noexcept { return exitGateId_; }

    /// Parked duration once closed; nullopt while still active.
    std::optional<Duration> duration() const;

    /**
     * Close the ticket on vehicle exit.
     * @throws InvalidArgumentException if already closed, gate empty, or exit < entry.
     */
    void close(TimePoint exitTime, std::string exitGateId);

private:
    Ticket(std::string id, std::shared_ptr<const Vehicle> vehicle,
           std::string spotId, int floorNumber, std::string entryGateId,
           TimePoint entryTime);

    friend class TicketBuilder;

    std::string id_;
    std::shared_ptr<const Vehicle> vehicle_;
    std::string spotId_;
    int floorNumber_;
    std::string entryGateId_;
    TimePoint entryTime_;
    TicketStatus status_ = TicketStatus::Active;
    std::optional<TimePoint> exitTime_;
    std::optional<std::string> exitGateId_;
};

}  // namespace pms
