#pragma once

#include <string>

#include "common/logging/ILogger.hpp"
#include "observer/IParkingObserver.hpp"

namespace pms {

/**
 * @class DisplayBoard
 * @brief Base for a board that re-renders whenever the lot changes.
 *
 * Combines Observer (it IS-A IParkingObserver) with Template Method:
 *   onParkingEvent() is the fixed reaction (prefix the board name, emit) while
 *   describe() — the bit that differs per board — is the hook each subtype fills.
 *   New board types only write describe(); they cannot get the wiring wrong.
 *
 * Output goes through ILogger (our display sink); a real deployment would
 * implement describe() the same way and push the string to a physical panel.
 */
class DisplayBoard : public IParkingObserver {
public:
    DisplayBoard(std::string name, ILogger& logger);

    void onParkingEvent(const ParkingEvent& event) final;
    const std::string& name() const noexcept { return name_; }

protected:
    virtual std::string describe(const ParkingEvent& event) const = 0;

private:
    std::string name_;
    ILogger& logger_;
};

}  // namespace pms
