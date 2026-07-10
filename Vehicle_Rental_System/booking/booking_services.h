#pragma once
#include "../user/user.h"
#include "../vehicle/vehicle.h"
#include "booking.h"
#include "../entity/status_type.h"
#include "../store/store.h"
#include "../payment/payment.h"
#include "../payment/cash_less.h"
#include "../payment/cash.h"
#include "../bill/bill.h"
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
    void createBooking(
        Vehicle* vehicle,
        User* user,
        string fromDate,
        string toDate,
        int totalDays
    )
    {
        if(vehicle->getStatus() != Status::AVAILABLE)
        {
            throw runtime_error(
                "Vehicle is not available"
            );
        }
        vehicle->updateStatus(Status::BOOKED);
        auto booking=make_unique<Booking> (
            bookingCounter++,
            vehicle,
            user,
            fromDate,
            toDate,
            totalDays
        );
        
        int n = 0;
    
        cout << "Select payment method to pay the booking amount: ₹ " << totalDays * booking->getVehicle()->getRentPrice() << endl;
        cout << "1. Online Payment" << endl;
        cout << "2. Cash Payment" << endl;
        cin >> n;
        unique_ptr<Payment> paymentMethod;

        if(n == 1){
        paymentMethod = make_unique<OnlinePayment>();
        } else {
        paymentMethod = make_unique<CashPayment>();
        }

        paymentMethod->pay();

        Bill bill(*booking);
        bill.generateBill();
        store.addBooking(move(booking));

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
            if(booking->getUser()->getId() == userId)
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
        booking->getVehicle()->updateStatus(Status::AVAILABLE);

    }


};