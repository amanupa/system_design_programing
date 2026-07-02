#include "factory/VehicleFactory.hpp"

#include "common/exceptions/ParkingException.hpp"
#include "domain/vehicle/Bike.hpp"
#include "domain/vehicle/Car.hpp"
#include "domain/vehicle/ElectricVehicle.hpp"
#include "domain/vehicle/Suv.hpp"
#include "domain/vehicle/Truck.hpp"
#include "domain/vehicle/VipVehicle.hpp"

namespace pms {

void VehicleFactory::registerType(VehicleType type, Creator creator) {
    if (!creator) {
        throw InvalidArgumentException("VehicleFactory: creator must not be null");
    }
    creators_[type] = std::move(creator);
}

bool VehicleFactory::isRegistered(VehicleType type) const noexcept {
    return creators_.find(type) != creators_.end();
}

std::unique_ptr<Vehicle> VehicleFactory::create(VehicleType type,
                                                const std::string& plate) const {
    const auto it = creators_.find(type);
    if (it == creators_.end()) {
        throw InvalidArgumentException(
            "VehicleFactory: no creator registered for vehicle type " + toString(type));
    }
    return it->second(plate);
}

VehicleFactory VehicleFactory::createDefault() {
    VehicleFactory factory;
    factory.registerType(VehicleType::Bike,
        [](const std::string& p) { return std::make_unique<Bike>(p); });
    factory.registerType(VehicleType::Car,
        [](const std::string& p) { return std::make_unique<Car>(p); });
    factory.registerType(VehicleType::Suv,
        [](const std::string& p) { return std::make_unique<Suv>(p); });
    factory.registerType(VehicleType::Truck,
        [](const std::string& p) { return std::make_unique<Truck>(p); });
    factory.registerType(VehicleType::ElectricVehicle,
        [](const std::string& p) { return std::make_unique<ElectricVehicle>(p); });
    factory.registerType(VehicleType::Vip,
        [](const std::string& p) { return std::make_unique<VipVehicle>(p); });
    return factory;
}

}  // namespace pms
