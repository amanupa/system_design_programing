#pragma once
#include "../booking/booking.h"
#include <iostream>
#include <string>
using namespace std;

class Bill{

private:
    static inline int globalBillCounter = 1;
    int billId;

    string userName;
    string licenseNumber;

    string vehicleNumber;
    string vehicleModel;

    string fromDate;
    string toDate;

    int totalCharge;


public:

    Bill(const Booking& booking)
    {
        billId=globalBillCounter++;

        userName = booking.getUser()->getUserName();
        licenseNumber = booking.getUser()->getDrivingLiscenceNumber();

        vehicleNumber = booking.getVehicle()->getRegistrationNumber();
        vehicleModel = booking.getVehicle()->getModel();

        fromDate = booking.getFromDate();
        toDate = booking.getToDate();

        totalCharge = booking.getTotalBookingDays() * booking.getVehicle()->getRentPrice();
    }


    void generateBill() const
    {
        cout<<"--------------Booking Confirmed-------------"<<endl;

        cout<<"User : "<<userName<<endl;
        cout<<"License : "<<licenseNumber<<endl;
        cout<<"Vehicle : "<<vehicleModel<<endl;
        cout<<"Vehicle Number : "<<vehicleNumber<<endl;
        cout<<"From : "<<fromDate<<endl;
        cout<<"To : "<<toDate<<endl;
        cout<<"Amount : "<<totalCharge<<endl;
        
        cout<<"--------------Thank you for booking with us. Visit again :-)"<<endl;
    }

    virtual ~Bill()=default;

};