#include "factory/SpotFactory.hpp"

#include "common/exceptions/ParkingException.hpp"
#include "domain/spot/BikeSpot.hpp"
#include "domain/spot/CarSpot.hpp"
#include "domain/spot/CompactSpot.hpp"
#include "domain/spot/ElectricSpot.hpp"
#include "domain/spot/HandicappedSpot.hpp"
#include "domain/spot/LargeSpot.hpp"
#include "domain/spot/TruckSpot.hpp"
#include "domain/spot/VipSpot.hpp"

namespace pms {

void SpotFactory::registerType(SpotType type, Creator creator) {
    if (!creator) {
        throw InvalidArgumentException("SpotFactory: creator must not be null");
    }
    creators_[type] = std::move(creator);
}

bool SpotFactory::isRegistered(SpotType type) const noexcept {
    return creators_.find(type) != creators_.end();
}

std::unique_ptr<ParkingSpot> SpotFactory::create(SpotType type,
                                                 const std::string& id,
                                                 int floor) const {
    const auto it = creators_.find(type);
    if (it == creators_.end()) {
        throw InvalidArgumentException(
            "SpotFactory: no creator registered for spot type " + toString(type));
    }
    return it->second(id, floor);
}

SpotFactory SpotFactory::createDefault() {
    SpotFactory factory;
    factory.registerType(SpotType::Bike,
        [](const std::string& id, int f) { return std::make_unique<BikeSpot>(id, f); });
    factory.registerType(SpotType::Compact,
        [](const std::string& id, int f) { return std::make_unique<CompactSpot>(id, f); });
    factory.registerType(SpotType::Car,
        [](const std::string& id, int f) { return std::make_unique<CarSpot>(id, f); });
    factory.registerType(SpotType::Large,
        [](const std::string& id, int f) { return std::make_unique<LargeSpot>(id, f); });
    factory.registerType(SpotType::Truck,
        [](const std::string& id, int f) { return std::make_unique<TruckSpot>(id, f); });
    factory.registerType(SpotType::Electric,
        [](const std::string& id, int f) { return std::make_unique<ElectricSpot>(id, f); });
    factory.registerType(SpotType::Vip,
        [](const std::string& id, int f) { return std::make_unique<VipSpot>(id, f); });
    factory.registerType(SpotType::Handicapped,
        [](const std::string& id, int f) { return std::make_unique<HandicappedSpot>(id, f); });
    return factory;
}

}  // namespace pms
