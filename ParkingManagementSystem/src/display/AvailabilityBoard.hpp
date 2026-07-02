#pragma once

#include <string>

#include "display/DisplayBoard.hpp"

namespace pms {

/// Shows overall free/total capacity and the change that just occurred.
class AvailabilityBoard final : public DisplayBoard {
public:
    explicit AvailabilityBoard(ILogger& logger)
        : DisplayBoard("Availability", logger) {}

protected:
    std::string describe(const ParkingEvent& event) const override {
        return "Available " + std::to_string(event.availability.availableSpots) +
               "/" + std::to_string(event.availability.totalSpots) + "  (" +
               toString(event.type) + " @ " + event.spotId + ")";
    }
};

}  // namespace pms
