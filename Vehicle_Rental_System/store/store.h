#pragma once
#include<memory>
#include "../inventory/inventory.h"
#include "../booking/booking.h"
#include <vector>
using namespace std;



class Store {
private:
    unique_ptr<Inventory> inventory;
    vector<unique_ptr<Booking>> bookings;

public:

    Store(unique_ptr<Inventory> inventory)
        : inventory(move(inventory)) 
    {}

    void addBooking(unique_ptr<Booking> booking)
    {
        bookings.push_back(move(booking));
    }

   const vector<unique_ptr<Booking>>& getBookings()const{
        return bookings;
    }

    Inventory* getInventory()
    {
        return inventory.get();
    }

    virtual ~Store() = default;
};