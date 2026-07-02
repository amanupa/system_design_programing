#pragma once

#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>

#include "../exceptions/ParkingException.hpp"

namespace pms {

/**
 * @class Money
 * @brief Immutable value object for currency amounts.
 *
 * Why it exists (vs. `double`):
 *   Floating point cannot represent decimal currency exactly (0.10 + 0.20 !=
 *   0.30), which produces rounding drift in billing. Money stores an integer
 *   count of *minor units* (paise/cents) so arithmetic is exact.
 *
 * Design:
 *   - Value object: identity is its value; equal amounts are interchangeable.
 *   - Immutable: operations return new instances (no aliasing surprises).
 *   - Encapsulation: callers never see the raw integer representation.
 *
 * Header-only: tiny, allocation-free, and inlining the arithmetic matters.
 */
class Money {
public:
    constexpr Money() noexcept : minorUnits_(0) {}

    /// Build from a whole-plus-fraction major amount, e.g. fromMajor(12, 50) == 12.50.
    static Money fromMajor(std::int64_t major, std::int64_t minor = 0) {
        if (minor < 0 || minor > 99) {
            throw InvalidArgumentException("Money: minor part must be in [0, 99]");
        }
        const std::int64_t sign = (major < 0) ? -1 : 1;
        return Money(major * 100 + sign * minor);
    }

    /// Build directly from minor units (cents/paise).
    static constexpr Money fromMinor(std::int64_t minorUnits) noexcept {
        return Money(minorUnits);
    }

    static constexpr Money zero() noexcept { return Money(0); }

    constexpr std::int64_t minorUnits() const noexcept { return minorUnits_; }
    constexpr bool isZero() const noexcept { return minorUnits_ == 0; }

    Money operator+(const Money& other) const noexcept {
        return Money(minorUnits_ + other.minorUnits_);
    }
    Money operator-(const Money& other) const noexcept {
        return Money(minorUnits_ - other.minorUnits_);
    }
    Money operator*(std::int64_t factor) const noexcept {
        return Money(minorUnits_ * factor);
    }

    /// p percent of this amount, truncated to the minor unit (e.g. 20% of 12.50
    /// -> 2.50). Integer math keeps it exact and rounding predictable (down).
    Money percent(std::int64_t p) const noexcept {
        return Money(minorUnits_ * p / 100);
    }

    bool operator==(const Money& o) const noexcept { return minorUnits_ == o.minorUnits_; }
    bool operator!=(const Money& o) const noexcept { return minorUnits_ != o.minorUnits_; }
    bool operator<(const Money& o)  const noexcept { return minorUnits_ <  o.minorUnits_; }
    bool operator<=(const Money& o) const noexcept { return minorUnits_ <= o.minorUnits_; }
    bool operator>(const Money& o)  const noexcept { return minorUnits_ >  o.minorUnits_; }
    bool operator>=(const Money& o) const noexcept { return minorUnits_ >= o.minorUnits_; }

    /// "12.50" style rendering (2 decimal places, handles negatives).
    std::string toString() const {
        std::ostringstream out;
        const std::int64_t abs = minorUnits_ < 0 ? -minorUnits_ : minorUnits_;
        if (minorUnits_ < 0) {
            out << '-';
        }
        out << (abs / 100) << '.' << std::setw(2) << std::setfill('0') << (abs % 100);
        return out.str();
    }

private:
    explicit constexpr Money(std::int64_t minorUnits) noexcept : minorUnits_(minorUnits) {}

    std::int64_t minorUnits_;
};

}  // namespace pms
