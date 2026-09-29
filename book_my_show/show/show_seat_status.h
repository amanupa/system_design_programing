#pragma once
#include <string>

enum class ShowSeatStatus { AVAILABLE, LOCKED, BOOKED };

inline std::string showSeatStatusToString(ShowSeatStatus status) {
    switch (status) {
        case ShowSeatStatus::AVAILABLE: return "AVAILABLE";
        case ShowSeatStatus::LOCKED: return "LOCKED";
        case ShowSeatStatus::BOOKED: return "BOOKED";
        default: return "UNKNOWN";
    }
}
