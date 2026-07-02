#include "factory/GateFactory.hpp"

#include "common/exceptions/ParkingException.hpp"
#include "domain/gate/EntryExitGate.hpp"
#include "domain/gate/EntryGate.hpp"
#include "domain/gate/ExitGate.hpp"

namespace pms {

void GateFactory::registerType(GateType type, Creator creator) {
    if (!creator) {
        throw InvalidArgumentException("GateFactory: creator must not be null");
    }
    creators_[type] = std::move(creator);
}

bool GateFactory::isRegistered(GateType type) const noexcept {
    return creators_.find(type) != creators_.end();
}

std::unique_ptr<Gate> GateFactory::create(GateType type,
                                          const std::string& id) const {
    const auto it = creators_.find(type);
    if (it == creators_.end()) {
        throw InvalidArgumentException(
            "GateFactory: no creator registered for gate type " + toString(type));
    }
    return it->second(id);
}

GateFactory GateFactory::createDefault() {
    GateFactory factory;
    factory.registerType(GateType::Entry,
        [](const std::string& id) { return std::make_unique<EntryGate>(id); });
    factory.registerType(GateType::Exit,
        [](const std::string& id) { return std::make_unique<ExitGate>(id); });
    factory.registerType(GateType::EntryExit,
        [](const std::string& id) { return std::make_unique<EntryExitGate>(id); });
    return factory;
}

}  // namespace pms
