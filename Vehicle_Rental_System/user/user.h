#pragma once
#include<string>
#include <iostream>
using namespace std;
class User{
    private:
    int userId;
    string name;
    string drivingLiscenceNumber;
    string phone;
    public:
    User(int id,string name, string dln,string phn):userId(id),name(name),drivingLiscenceNumber(dln),phone(phn){}

    string getDrivingLiscenceNumber() const{
        return drivingLiscenceNumber;

    }
    int getId() const{
        return userId;
    }
    string getUserName()const{
        return name;
    }
    virtual ~User()=default;
};