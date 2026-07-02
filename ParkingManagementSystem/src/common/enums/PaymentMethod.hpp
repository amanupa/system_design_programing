#pragma once

#include <string>

namespace pms {

/**
 * @enum PaymentMethod
 * @brief Supported settlement channels.
 *
 * Each method maps to a concrete payment Strategy (Phase 8). New methods are
 * added by introducing a new strategy + registration, not by editing callers.
 */
enum class PaymentMethod {
    Cash,
    Card,
    Upi
};

inline std::string toString(PaymentMethod method) {
    switch (method) {
        case PaymentMethod::Cash: return "Cash";
        case PaymentMethod::Card: return "Card";
        case PaymentMethod::Upi:  return "UPI";
    }
    return "Unknown";
}

}  // namespace pms
