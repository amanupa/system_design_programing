// Parking Management System — composition root.
//
// Wires the cross-cutting dependencies, loads configuration, builds the
// ParkingLot facade from it, and hands control to the CLI (or a scripted demo).
// All construction happens here; nothing below owns a global.

#include <iostream>
#include <string>

#include "common/logging/ConsoleLogger.hpp"
#include "common/util/SequentialIdGenerator.hpp"
#include "common/util/SystemClock.hpp"
#include "config/ConfigurationManager.hpp"
#include "config/DefaultConfigurationSource.hpp"
#include "facade/ParkingLot.hpp"
#include "presentation/CliApp.hpp"

using namespace pms;

int main(int argc, char** argv) {
    // Cross-cutting dependencies (the only concretions created in the whole app).
    ConsoleLogger logger(LogLevel::Info);
    SystemClock clock;
    SequentialIdGenerator idGenerator;

    // Configuration -> the validated single source of truth.
    DefaultConfigurationSource configSource;
    ConfigurationManager configManager(configSource, logger);

    // The whole system, assembled from configuration behind one facade.
    ParkingLot lot(configManager.config(), logger, clock, idGenerator);

    if (argc > 1 && std::string(argv[1]) == "--demo") {
        runDemo(lot, std::cout);
        return 0;
    }

    CliApp app(lot, std::cin, std::cout);
    return app.run();
}
