#include <iostream>
#include <memory>
#include<chrono>
#include "location/location.h"
#include "rental_system/rental_system.h"
#include "store/store.h"
#include "inventory/inventory.h"
#include "booking/booking.h"
#include "booking/booking_services.h"
#include "vehicle/vehicle.h"
#include "vehicle/car.h"
#include "user/user.h"
#include "entity/engine_type.h"
#include "entity/status_type.h"
#include "payment/payment.h"
#include "payment/cash_less.h"
#include "payment/cash.h"
#include "bill/bill.h"
using namespace std;
using namespace chrono;
int main()
{

    cout<<"Welcome to the Vehicle Rental System"<<endl;

    VehicleRentalSystem vehicleRentalSystem;
    unique_ptr<Payment> paymentMethod;


    auto chandigarh = make_unique<Location>();

    auto inventory1 = make_unique<Inventory>();


    auto car1 = make_unique<Car>(
        1,
        "CH010001",
        "Toyota",
        "Fortuner Legender",
        10000,
        Engine::PETROL,
        Status::AVAILABLE,
        15,
        4
    );


    Vehicle& car1Ref = *car1;


    inventory1->addVehicle(
        std::move(car1)
    );


    auto store1 = make_unique<Store>(
        std::move(inventory1)
    );


    Store& storeRef = *store1;


    chandigarh->addStore(
        std::move(store1)
    );


    vehicleRentalSystem.addLocation(
        std::move(chandigarh)
    );


    auto user = make_shared<User>(
        1,
        "Aman",
        "DL0001",
        "11111011111"
    );
    User& userRef=*user.get();


    BookingServices bookingService(
        storeRef
    );

    auto start = high_resolution_clock::now();
    auto booking=bookingService.createBooking(
        car1Ref,
        userRef,
        "10-07-2026",
        "12-07-2026",
        2
    );
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end-start);
    cout << "Execution time: " << duration.count() << " ms" << endl;
    

    int n = 0;
    
        cout << "Select payment method to pay the booking amount: ₹ " << booking->getTotalBookingDays() * booking->getVehicle().getRentPrice() << endl;
        cout << "1. Online Payment" << endl;
        cout << "2. Cash Payment" << endl;
        cin >> n;

        if(n == 1){
        paymentMethod = make_unique<OnlinePayment>();
        } else {
        paymentMethod = make_unique<CashPayment>();
        }
        paymentMethod->pay();

    Bill bill(*booking);
    bill.generateBill();

    return 0;
}