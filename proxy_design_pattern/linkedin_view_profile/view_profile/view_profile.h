#pragma once
#include<vector>
#include<iostream>
#include "../user.h"
using namespace std;

class IProfileView{
    public:
    virtual vector<User>getProfileViewer(int id, User& usr)=0;
    virtual ~IProfileView()=default;
};