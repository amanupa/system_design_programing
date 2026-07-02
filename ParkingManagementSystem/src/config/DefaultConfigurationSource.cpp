#include "config/DefaultConfigurationSource.hpp"

#include "config/ParkingLotConfigBuilder.hpp"

namespace pms {

ParkingLotConfig DefaultConfigurationSource::load() const {
    PricingConfig pricing;
    pricing.scheme = PricingScheme::Hourly;
    pricing.baseRate = Money::fromMajor(40);
    pricing.vipDiscountEnabled = true;
    pricing.vipDiscountPercent = 20;
    pricing.electricSurchargeEnabled = true;
    pricing.electricSurcharge = Money::fromMajor(50);

    return ParkingLotConfigBuilder()
        .name("Downtown Plaza Parking")
        .addFloor(1, {{SpotType::Bike, 10},
                      {SpotType::Compact, 10},
                      {SpotType::Car, 10},
                      {SpotType::Electric, 4},
                      {SpotType::Vip, 2},
                      {SpotType::Handicapped, 2},
                      {SpotType::Large, 2}})
        .addFloor(2, {{SpotType::Car, 20},
                      {SpotType::Large, 5},
                      {SpotType::Truck, 3},
                      {SpotType::Electric, 4}})
        .addGate("GATE-IN-1", GateType::Entry)
        .addGate("GATE-IN-2", GateType::Entry)
        .addGate("GATE-OUT-1", GateType::Exit)
        .addGate("GATE-IO-1", GateType::EntryExit)
        .pricing(pricing)
        .build();
}

}  // namespace pms
