#include "domain/ticket/Ticket.hpp"

#include <utility>

#include "common/exceptions/ParkingException.hpp"

namespace pms {

Ticket::Ticket(std::string id, std::shared_ptr<const Vehicle> vehicle,
               std::string spotId, int floorNumber, std::string entryGateId,
               TimePoint entryTime)
    : id_(std::move(id)),
      vehicle_(std::move(vehicle)),
      spotId_(std::move(spotId)),
      floorNumber_(floorNumber),
      entryGateId_(std::move(entryGateId)),
      entryTime_(entryTime) {}

std::optional<Duration> Ticket::duration() const {
    if (!exitTime_.has_value()) {
        return std::nullopt;
    }
    return std::chrono::duration_cast<Duration>(*exitTime_ - entryTime_);
}

void Ticket::close(TimePoint exitTime, std::string exitGateId) {
    if (status_ == TicketStatus::Closed) {
        throw InvalidArgumentException("Ticket " + id_ + " is already closed");
    }
    if (exitGateId.empty()) {
        throw InvalidArgumentException("Ticket::close: exit gate id is empty");
    }
    if (exitTime < entryTime_) {
        throw InvalidArgumentException("Ticket::close: exit time precedes entry time");
    }
    exitTime_ = exitTime;
    exitGateId_ = std::move(exitGateId);
    status_ = TicketStatus::Closed;
}

}  // namespace pms
