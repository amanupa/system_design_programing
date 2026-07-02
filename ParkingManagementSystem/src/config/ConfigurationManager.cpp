#include "config/ConfigurationManager.hpp"

namespace pms {

ConfigurationManager::ConfigurationManager(const IConfigurationSource& source,
                                           ILogger& logger)
    : source_(source), logger_(logger), config_(source.load()) {
    logger_.info("Loaded configuration '" + config_.name() + "': " +
                 std::to_string(config_.floorCount()) + " floor(s), " +
                 std::to_string(config_.totalConfiguredSpots()) + " spot(s), " +
                 std::to_string(config_.gateCount()) + " gate(s), pricing=" +
                 toString(config_.pricing().scheme));
}

void ConfigurationManager::reload() {
    config_ = source_.load();
    logger_.info("Configuration reloaded: '" + config_.name() + "'");
}

}  // namespace pms
