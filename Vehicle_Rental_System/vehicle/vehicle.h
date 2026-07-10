#pragma once 
#include<iostream>
#include<string>
#include "../entity/engine_type.h"
#include "../entity/status_type.h"
using namespace std;


class Vehicle{
    private:
    int id;
    const string registrationNumber;
    const string brand;
    const string model;
    int rentPrice;
    Engine type;
    Status status;
    public:

    Vehicle(int id, string regn, string brnd,string modl,int rp, Engine t,Status st):id(id),registrationNumber(regn),model(modl),brand(brnd),rentPrice(rp),type(t),status(st){}

    string getRegistrationNumber()const{
        return registrationNumber;
    }
    int getRentPrice()const{
        return rentPrice;
    }

    void updateStatus(Status newStatus){
        status=newStatus;

    }

    int getVehicleId()const{
        return id;
    }

    Status getStatus(){
        return status;
    }

    bool isVehicleAvailable(){
        return status == Status::AVAILABLE;
    }
    string getModel()const{
        return model;
    }

    virtual ~Vehicle()=default;

};