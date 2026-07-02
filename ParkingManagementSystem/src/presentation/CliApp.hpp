#pragma once

#include <iosfwd>
#include <optional>
#include <string>

#include "common/enums/PaymentMethod.hpp"
#include "common/enums/VehicleType.hpp"
#include "facade/ParkingLot.hpp"

namespace pms {

/**
 * @class CliApp
 * @brief Interactive console front-end over the ParkingLot facade.
 *
 * Presentation layer only: it parses user input, calls the facade, and renders
 * results/errors. It contains no business logic. Streams are injected
 * (std::istream&/std::ostream&) so the UI can be driven by a scripted input in
 * tests, not just the real console.
 *
 * SOLID: SRP (user interaction), DIP (depends on the ParkingLot facade and on
 * stream abstractions, not on concrete devices).
 */
class CliApp {
public:
    CliApp(ParkingLot& lot, std::istream& in, std::ostream& out) noexcept;

    /// Run the menu loop until Quit or end-of-input. Returns a process exit code.
    int run();

private:
    void printMenu() const;
    void handlePark();
    void handleExit();
    void handleStatus() const;
    void handleGateAdmin();
    void handleReports() const;

    std::optional<std::string> readLine(const std::string& prompt) const;
    std::optional<VehicleType> promptVehicleType() const;
    std::optional<PaymentMethod> promptPaymentMethod() const;

    ParkingLot& lot_;
    std::istream& in_;
    std::ostream& out_;
};

/// Non-interactive scripted scenario (used by the `--demo` flag).
void runDemo(ParkingLot& lot, std::ostream& out);

}  // namespace pms
