#pragma once

#include <string>

#include "display/DisplayBoard.hpp"

namespace pms {

/// Dedicated board showing how many VIP spots remain free.
class VipBoard final : public DisplayBoard {
public:
    explicit VipBoard(ILogger& logger) : DisplayBoard("VIP", logger) {}

protected:
    std::string describe(const ParkingEvent& event) const override {
        return "VIP spots free: " + std::to_string(event.availability.availableVip);
    }
};

}  // namespace pms
