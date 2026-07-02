#pragma once

#include <string>

namespace pms {

/**
 * @enum PaymentStatus
 * @brief Outcome/lifecycle state of a payment record.
 *
 * Pending is reserved for future asynchronous channels; today's strategies
 * settle synchronously, so a record is created already Success or Failed, and
 * a successful one may later become Refunded.
 */
enum class PaymentStatus {
    Pending,
    Success,
    Failed,
    Refunded
};

inline std::string toString(PaymentStatus status) {
    switch (status) {
        case PaymentStatus::Pending:  return "Pending";
        case PaymentStatus::Success:  return "Success";
        case PaymentStatus::Failed:   return "Failed";
        case PaymentStatus::Refunded: return "Refunded";
    }
    return "Unknown";
}

}  // namespace pms
