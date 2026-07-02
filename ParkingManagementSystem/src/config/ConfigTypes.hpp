#pragma once

#include <cstddef>
#include <map>
#include <set>
#include <string>

#include "common/enums/GateType.hpp"
#include "common/enums/SpotType.hpp"
#include "common/util/Money.hpp"

namespace pms {

/// Which base fee scheme the lot uses (decorators for VIP/EV layer on top).
enum class PricingScheme {
    Hourly,
    Daily,
    Weekend,
    Holiday
};

inline std::string toString(PricingScheme scheme) {
    switch (scheme) {
        case PricingScheme::Hourly:  return "Hourly";
        case PricingScheme::Daily:   return "Daily";
        case PricingScheme::Weekend: return "Weekend";
        case PricingScheme::Holiday: return "Holiday";
    }
    return "Unknown";
}

/// One floor's identity and how many spots of each type it has.
struct FloorConfig {
    int floorNumber = 0;
    std::map<SpotType, int> spotCounts;

    std::size_t totalSpots() const {
        std::size_t total = 0;
        for (const auto& [type, count] : spotCounts) {
            (void)type;
            if (count > 0) {
                total += static_cast<std::size_t>(count);
            }
        }
        return total;
    }
};

/// One gate's identity and capability.
struct GateConfig {
    std::string id;
    GateType type = GateType::EntryExit;
};

/// Pricing definition: base scheme + the optional adjustment decorators.
struct PricingConfig {
    PricingScheme scheme = PricingScheme::Hourly;
    Money baseRate = Money::fromMajor(40);      // hourly/daily/weekday/normal rate
    Money premiumRate = Money::fromMajor(60);   // weekend/holiday rate (if scheme uses it)
    std::set<std::string> holidays;             // "YYYY-MM-DD" entries for Holiday scheme

    bool vipDiscountEnabled = true;
    int vipDiscountPercent = 20;

    bool electricSurchargeEnabled = true;
    Money electricSurcharge = Money::fromMajor(50);
};

}  // namespace pms
