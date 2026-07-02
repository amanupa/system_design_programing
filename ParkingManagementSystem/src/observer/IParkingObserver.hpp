#pragma once

#include "domain/event/ParkingEvent.hpp"

namespace pms {

/**
 * @class IParkingObserver
 * @brief Observer side of the Observer pattern — reacts to lot changes.
 *
 * Anything that must react when the lot changes (display boards, metrics
 * collectors, alerting) implements this one method. The subject pushes the
 * event; the observer decides what to do (ISP: one focused responsibility).
 */
class IParkingObserver {
public:
    virtual ~IParkingObserver() = default;
    virtual void onParkingEvent(const ParkingEvent& event) = 0;
};

}  // namespace pms
