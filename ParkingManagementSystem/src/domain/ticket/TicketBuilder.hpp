#pragma once

#include <memory>
#include <optional>
#include <string>

#include "common/util/Time.hpp"
#include "domain/ticket/Ticket.hpp"
#include "domain/vehicle/Vehicle.hpp"

namespace pms {

/**
 * @class TicketBuilder
 * @brief Fluent, validating builder — the only way to construct a Ticket.
 *
 * Pattern: Builder.
 *   Justified by the number of mandatory fields and the readability win of named
 *   setters over a positional 6-arg constructor (which invites silent argument
 *   swaps between same-typed parameters). build() enforces all invariants in one
 *   place, so every Ticket that exists is valid by construction.
 *
 * Each setter returns *this to allow chaining:
 *   TicketBuilder().id(...).vehicle(...).spotId(...)....build();
 *
 * SOLID: SRP (assembling+validating a Ticket), and it keeps that concern out of
 * the entity itself.
 */
class TicketBuilder {
public:
    TicketBuilder& id(std::string id);
    TicketBuilder& vehicle(std::shared_ptr<const Vehicle> vehicle);
    TicketBuilder& spotId(std::string spotId);
    TicketBuilder& floorNumber(int floorNumber);
    TicketBuilder& entryGateId(std::string entryGateId);
    TicketBuilder& entryTime(TimePoint entryTime);

    /// @throws InvalidArgumentException if any required field is missing/invalid.
    Ticket build() const;

private:
    std::optional<std::string> id_;
    std::shared_ptr<const Vehicle> vehicle_;
    std::optional<std::string> spotId_;
    std::optional<int> floorNumber_;
    std::optional<std::string> entryGateId_;
    std::optional<TimePoint> entryTime_;
};

}  // namespace pms
