#pragma once 
#include "notify_observer.h"
#include<iostream>
using namespace std;
class IphoneObservable;

class EmailNotifyObserver : public NotifyObserver{
    private:
    string email;
    IphoneObservable* iphoneobservale;

    void sendMail(string mail, string msg){
        cout<<"mail sent to: "<<mail<<endl;
    }
    public:
    EmailNotifyObserver(IphoneObservable* io, string email){
        this->iphoneobservale=io;
        this->email=email;
    }

    void notifyObservers() override{
        sendMail(email,"product is in stock");

    }

};