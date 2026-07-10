#pragma once 


class Payment{
    public:
    virtual void pay()=0;

    virtual ~Payment()=default;

};