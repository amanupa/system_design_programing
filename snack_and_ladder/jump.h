#pragma once 
#include<iostream>
using namespace std;

class Jump{
    private:
    int start;
    int end;
    public:
    Jump(int st, int en):start(st),end(en){}

    int getStart()const{
    return start;
    }
    int getEnd()const{
    return end;
    }
    virtual ~Jump()=default;
};