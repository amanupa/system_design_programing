#pragma once

#include <string>

namespace pms {

/**
 * @enum TicketStatus
 * @brief Lifecycle state of a parking ticket.
 *
 * A ticket is Active from issue until the vehicle exits, then Closed exactly
 * once. (Lost/void states could be added later without touching existing code.)
 */
enum class TicketStatus {
    Active,
    Closed
};

inline std::string toString(TicketStatus status) {
    switch (status) {
        case TicketStatus::Active: return "Active";
        case TicketStatus::Closed: return "Closed";
    }
    return "Unknown";
}

}  // namespace pms
