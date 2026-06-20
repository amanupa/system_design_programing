#include <iostream>
using namespace std;

#include "observable/iphone_observable.h"
#include "observable/stock_observable.h"

#include "observer/notify_observer.h"
#include "observer/email_observer.h"
#include "observer/phone_observer.h"



int main() {
    // 1. Create the Product (Observable)
    IphoneObservable* iphoneStock = new IphoneObservable();

    // 2. Create Customers (Observers) passing in their email and the product they are watching
    NotifyObserver* user1 = new EmailNotifyObserver(iphoneStock,"alice@example.com");

    NotifyObserver* user2 = new PhoneNotifyObserver(iphoneStock,"9241867776");

    // 3. Customers click "Notify Me"
    iphoneStock->addObservers(user1);
    iphoneStock->addObservers(user2);

    std::cout << "--- Shipment 1 arrives (10 iPhones) ---" << std::endl;
    // Stock goes from 0 to 10. This SHOULD trigger notifications.
    iphoneStock->updateStock(10); 

    std::cout << "\n--- Shipment 2 arrives (5 more iPhones) ---" << std::endl;
    // Stock goes from 10 to 15. This should NOT trigger notifications (already in stock).
    iphoneStock->updateStock(5); 

    // Clean up memory
    delete user1;
    delete user2;
    delete iphoneStock;

    return 0;
}