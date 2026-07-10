#pragma once
#include"../vehicle/vehicle.h"
#include "../user/user.h"
#include<string>
#include<iostream>
#include <memory>
using namespace std;
class Booking{
    private:
    int bookingId;
    Vehicle* vehicle;
    User* user;
    string fromDate;
    string toDate;
    int totalDays;
    public:
    Booking(int bookingId, Vehicle* vehicle, User* user,string fromDate, string toDate,int totalDays): bookingId(bookingId),vehicle(vehicle),user(user),fromDate(fromDate), toDate(toDate), totalDays(totalDays){}

    int getBookingId() const{
        return bookingId;

    }
    Vehicle* getVehicle()const{
        return vehicle;
    }

    User* getUser()const{
        return user;
    }
    string getFromDate()const{
         return fromDate;
    }
    string getToDate() const{
        return toDate;
    }

    int getTotalBookingDays()const{
        return totalDays;
    }

    virtual ~Booking()=default;

};