#pragma once
#include <string>

enum class SeatType {
    BASIC,
    PREMIUM,
    LUXERY
};

inline std::string seatTypeToString(SeatType type) {
    switch (type) {
        case SeatType::BASIC: return "BASIC";
        case SeatType::PREMIUM: return "PREMIUM";
        case SeatType::LUXERY: return "LUXURY";
        default: return "UNKNOWN";
    }
}