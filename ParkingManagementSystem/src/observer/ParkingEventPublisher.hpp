#pragma once

#include <cstddef>
#include <vector>

#include "domain/event/ParkingEvent.hpp"
#include "observer/IParkingObserver.hpp"
#include "observer/IParkingSubject.hpp"

namespace pms {

/**
 * @class ParkingEventPublisher
 * @brief Reusable concrete subject: keeps a list of observers and notifies them.
 *
 * Designed to be HELD by an event source (SpotManager composes one) rather than
 * inherited — composition over inheritance keeps the source's own interface
 * clean and lets the same publisher serve any future source.
 *
 * Observers are stored as non-owning pointers (the subject does not control
 * their lifetime). subscribe() ignores nulls and duplicates.
 */
class ParkingEventPublisher : public IParkingSubject {
public:
    void subscribe(IParkingObserver* observer) override;
    void unsubscribe(IParkingObserver* observer) override;

    /// Notify every current observer. const: publishing doesn't change the list.
    void publish(const ParkingEvent& event) const;

    std::size_t observerCount() const noexcept { return observers_.size(); }

private:
    std::vector<IParkingObserver*> observers_;
};

}  // namespace pms
