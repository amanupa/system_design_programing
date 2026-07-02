#pragma once

#include <string>

namespace pms {

/**
 * @enum GateStatus
 * @brief Operational state of a gate.
 *
 * Modelled as the set of states for the State pattern (Phase 6). A gate only
 * serves traffic in the Open state; Closed/Maintenance/Disabled reject
 * operations with clear, state-specific behaviour.
 */
enum class GateStatus {
    Open,         // serving traffic
    Closed,       // temporarily not serving, can be reopened
    Maintenance,  // under service, rejects all traffic
    Disabled      // administratively removed from rotation
};

inline std::string toString(GateStatus status) {
    switch (status) {
        case GateStatus::Open:        return "Open";
        case GateStatus::Closed:      return "Closed";
        case GateStatus::Maintenance: return "Maintenance";
        case GateStatus::Disabled:    return "Disabled";
    }
    return "Unknown";
}

}  // namespace pms
