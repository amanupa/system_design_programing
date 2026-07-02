#include "display/DisplayManager.hpp"

#include <utility>

#include "common/exceptions/ParkingException.hpp"

namespace pms {

DisplayManager::DisplayManager(IParkingSubject& subject, ILogger& logger) noexcept
    : subject_(subject), logger_(logger) {}

DisplayManager::~DisplayManager() {
    // Detach every board so the subject never calls into freed observers.
    for (const std::unique_ptr<DisplayBoard>& board : boards_) {
        subject_.unsubscribe(board.get());
    }
}

void DisplayManager::addBoard(std::unique_ptr<DisplayBoard> board) {
    if (!board) {
        throw InvalidArgumentException("DisplayManager::addBoard: board is null");
    }
    subject_.subscribe(board.get());
    logger_.info("Display board registered: " + board->name());
    boards_.push_back(std::move(board));
}

}  // namespace pms
