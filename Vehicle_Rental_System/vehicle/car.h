#pragma once 
#include<iostream>
#include<string>
#include "vehicle.h"
using namespace std;

class Car:public Vehicle{
    private:
    int seater;
    int milage;
    public:
    Car(int id,const string& registrationNumber,const string& brand,const string& model,
    int rentPrice,
    Engine type,
    Status status,int milgage,int seat):Vehicle(id,registrationNumber,brand,model,rentPrice,type,status),
    milage(milgage),seater(seat){}

    virtual ~Car()=default;

};