#pragma once

namespace pms {

class IParkingObserver;

/**
 * @class IParkingSubject
 * @brief Subject side of the Observer pattern — manages subscriptions.
 *
 * Consumers depend on this abstraction to (un)subscribe, never on the concrete
 * publisher or on SpotManager (DIP). Observers are referenced non-owningly;
 * their lifetime belongs to whoever created them (e.g. DisplayManager).
 */
class IParkingSubject {
public:
    virtual ~IParkingSubject() = default;
    virtual void subscribe(IParkingObserver* observer) = 0;
    virtual void unsubscribe(IParkingObserver* observer) = 0;
};

}  // namespace pms
