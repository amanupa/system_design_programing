#include "observer/ParkingEventPublisher.hpp"

#include <algorithm>

namespace pms {

void ParkingEventPublisher::subscribe(IParkingObserver* observer) {
    if (observer == nullptr) {
        return;
    }
    if (std::find(observers_.begin(), observers_.end(), observer) ==
        observers_.end()) {
        observers_.push_back(observer);
    }
}

void ParkingEventPublisher::unsubscribe(IParkingObserver* observer) {
    observers_.erase(std::remove(observers_.begin(), observers_.end(), observer),
                     observers_.end());
}

void ParkingEventPublisher::publish(const ParkingEvent& event) const {
    for (IParkingObserver* observer : observers_) {
        observer->onParkingEvent(event);
    }
}

}  // namespace pms
