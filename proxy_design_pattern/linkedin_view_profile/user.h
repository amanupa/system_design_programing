#pragma once
#include <iostream>
#include<string>
#include "subscription_type.h"
using namespace std;

class User{
    private:
    int id;
    string name;
    string job;
    SubscriptionType type;

    public:
    User(int id,string name, string job, SubscriptionType type):id(id),name(name), job(job),type(type){}

    string getUserName()const{
        return name;
    }
    int getUserId()const{
        return id;
    }

    SubscriptionType getSubscriptionType(){
        return type;
    }

    virtual ~User()=default;

};