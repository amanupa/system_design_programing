#pragma once

#include <string>

#include "display/DisplayBoard.hpp"

namespace pms {

/// Dedicated board showing how many charging (electric) spots remain free.
class ElectricBoard final : public DisplayBoard {
public:
    explicit ElectricBoard(ILogger& logger) : DisplayBoard("Charging", logger) {}

protected:
    std::string describe(const ParkingEvent& event) const override {
        return "Charging spots free: " +
               std::to_string(event.availability.availableElectric);
    }
};

}  // namespace pms
