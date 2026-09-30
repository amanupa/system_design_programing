#pragma once
#include <string>

enum class BookingStatus {
    PENDING,
    CONFIRMED,
    CANCELLED
};

inline std::string bookingStatusToString(BookingStatus status) {
    switch (status) {
        case BookingStatus::PENDING: return "PENDING";
        case BookingStatus::CONFIRMED: return "CONFIRMED";
        case BookingStatus::CANCELLED: return "CANCELLED";
        default: return "UNKNOWN";
    }
}
