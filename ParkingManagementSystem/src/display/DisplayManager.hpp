#pragma once

#include <cstddef>
#include <memory>
#include <vector>

#include "common/logging/ILogger.hpp"
#include "display/DisplayBoard.hpp"
#include "observer/IParkingSubject.hpp"

namespace pms {

/**
 * @class DisplayManager
 * @brief Owns the display boards and wires them to the lot's event source.
 *
 * Adding a board subscribes it to the injected subject; the destructor
 * unsubscribes every board, so a board can never be notified after it (or the
 * manager) is gone — no dangling observers. The manager depends on
 * IParkingSubject, not on SpotManager (DIP).
 *
 * SOLID: SRP (board lifecycle + subscription), DIP, OCP (any DisplayBoard works).
 */
class DisplayManager {
public:
    DisplayManager(IParkingSubject& subject, ILogger& logger) noexcept;
    ~DisplayManager();

    DisplayManager(const DisplayManager&) = delete;
    DisplayManager& operator=(const DisplayManager&) = delete;

    /// Take ownership of a board and subscribe it to the event source.
    void addBoard(std::unique_ptr<DisplayBoard> board);

    std::size_t boardCount() const noexcept { return boards_.size(); }

private:
    IParkingSubject& subject_;
    ILogger& logger_;
    std::vector<std::unique_ptr<DisplayBoard>> boards_;
};

}  // namespace pms
