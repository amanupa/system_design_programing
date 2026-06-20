#pragma once
#include "notify_observer.h"
#include<iostream>
using namespace std;
class IphoneObservable;

class PhoneNotifyObserver : public NotifyObserver{
    private:
    string phone;
    IphoneObservable* iphoneobservale;

    void sendMail(string ph, string msg){
        cout<<"msg sent to phone no: "<<ph<<endl;
    }
    public:
    PhoneNotifyObserver(IphoneObservable* io, string phone){
        this->iphoneobservale=io;
        this->phone=phone;
    }

    void notifyObservers() override{
        sendMail(phone,"product is in stock hurry up");

    }

};