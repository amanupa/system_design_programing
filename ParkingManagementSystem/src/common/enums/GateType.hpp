#pragma once

#include <string>

namespace pms {

/**
 * @enum GateType
 * @brief Capability of a gate.
 *
 * Drives which operations a gate may perform:
 *   - Entry      : may issue parking tickets only.
 *   - Exit       : may process exits/payments only.
 *   - EntryExit  : may do both.
 *
 * Enforcement is done through the type hierarchy + interfaces (Phase 6, ISP),
 * not by scattering `if (type == ...)` checks across the codebase.
 */
enum class GateType {
    Entry,
    Exit,
    EntryExit
};

inline std::string toString(GateType type) {
    switch (type) {
        case GateType::Entry:     return "Entry";
        case GateType::Exit:      return "Exit";
        case GateType::EntryExit: return "EntryExit";
    }
    return "Unknown";
}

}  // namespace pms
