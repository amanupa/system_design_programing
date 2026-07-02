#include "domain/ticket/TicketBuilder.hpp"

#include <utility>

#include "common/exceptions/ParkingException.hpp"

namespace pms {

TicketBuilder& TicketBuilder::id(std::string id) {
    id_ = std::move(id);
    return *this;
}

TicketBuilder& TicketBuilder::vehicle(std::shared_ptr<const Vehicle> vehicle) {
    vehicle_ = std::move(vehicle);
    return *this;
}

TicketBuilder& TicketBuilder::spotId(std::string spotId) {
    spotId_ = std::move(spotId);
    return *this;
}

TicketBuilder& TicketBuilder::floorNumber(int floorNumber) {
    floorNumber_ = floorNumber;
    return *this;
}

TicketBuilder& TicketBuilder::entryGateId(std::string entryGateId) {
    entryGateId_ = std::move(entryGateId);
    return *this;
}

TicketBuilder& TicketBuilder::entryTime(TimePoint entryTime) {
    entryTime_ = entryTime;
    return *this;
}

Ticket TicketBuilder::build() const {
    if (!id_ || id_->empty()) {
        throw InvalidArgumentException("TicketBuilder: id is required");
    }
    if (!vehicle_) {
        throw InvalidArgumentException("TicketBuilder: vehicle is required");
    }
    if (!spotId_ || spotId_->empty()) {
        throw InvalidArgumentException("TicketBuilder: spotId is required");
    }
    if (!floorNumber_) {
        throw InvalidArgumentException("TicketBuilder: floorNumber is required");
    }
    if (!entryGateId_ || entryGateId_->empty()) {
        throw InvalidArgumentException("TicketBuilder: entryGateId is required");
    }
    if (!entryTime_) {
        throw InvalidArgumentException("TicketBuilder: entryTime is required");
    }
    // All validated — construct via Ticket's private ctor (we are its friend).
    return Ticket(*id_, vehicle_, *spotId_, *floorNumber_, *entryGateId_, *entryTime_);
}

}  // namespace pms
