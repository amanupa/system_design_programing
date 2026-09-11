#pragma once
#include "../user/user.h"
#include "../vehicle/vehicle.h"
#include "booking.h"
#include "../entity/status_type.h"
#include "../store/store.h"
#include<vector>
#include<iostream>
#include <memory>
#include <string>
using namespace std;

class BookingServices{
    private:
    Store& store;
    int bookingCounter=1;
    public:
    BookingServices(Store& store):store(store){}
    Booking* createBooking(
        Vehicle& vehicle,
        User& user,
        string fromDate,
        string toDate,
        int totalDays
    )
    {
        if(vehicle.getStatus() != Status::AVAILABLE)
        {
            throw runtime_error(
                "Vehicle is not available"
            );
        }
        vehicle.updateStatus(Status::BOOKED);
        auto booking=make_unique<Booking> (
            bookingCounter++,
            vehicle,
            user,
            fromDate,
            toDate,
            totalDays
        );
        auto result=booking.get();
        store.addBooking(move(booking));
        return result;

    }
    
    Booking* getBooking(int bookingId){
        const auto& bookings=store.getBookings();

        for(auto& booking : bookings)
        {
            if(booking->getBookingId() == bookingId)
            {
                return booking.get();
            }
        }
        return nullptr;
    }

    vector<Booking*> getAllBookings()
{
    vector<Booking*> allBookings;

    const auto& bookings = store.getBookings();

    for(auto& booking : bookings)
    {
        allBookings.push_back(booking.get());
    }

    return allBookings;
}

    vector<Booking*> getUserBookings(int userId)
    {
        vector<Booking*> userBookings;
       const auto& bookings=store.getBookings();
        for(auto& booking : bookings)
        {
            if(booking->getUser().getId() == userId)
            {
                userBookings.push_back(booking.get());
            }
        }
        return userBookings;
    }

    void completeBooking(int bookingId){
        Booking* booking = getBooking(bookingId);
        if(booking == nullptr)
        {
            throw runtime_error(
                "Booking not found"
            );
        }
        booking->getVehicle().updateStatus(Status::AVAILABLE);

    }


};