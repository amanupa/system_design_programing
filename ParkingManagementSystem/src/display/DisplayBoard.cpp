#include "display/DisplayBoard.hpp"

#include <utility>

namespace pms {

DisplayBoard::DisplayBoard(std::string name, ILogger& logger)
    : name_(std::move(name)), logger_(logger) {}

void DisplayBoard::onParkingEvent(const ParkingEvent& event) {
    logger_.info("[BOARD:" + name_ + "] " + describe(event));
}

}  // namespace pms
