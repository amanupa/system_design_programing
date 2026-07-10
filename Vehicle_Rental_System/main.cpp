#include <iostream>
#include <memory>
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
using namespace std;
int main()
{

    cout<<"Welcome to the Vehicle Rental System"<<endl;

    VehicleRentalSystem vehicleRentalSystem;


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


    Vehicle* carPtr = car1.get();


    inventory1->addVehicle(
        std::move(car1)
    );


    auto store1 = make_unique<Store>(
        std::move(inventory1)
    );


    Store* storePtr = store1.get();


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


    BookingServices bookingService(
        *storePtr
    );


    bookingService.createBooking(
        carPtr,
        user.get(),
        "10-07-2026",
        "12-07-2026",
        2
    );

    return 0;
}