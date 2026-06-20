#pragma once 

class NotifyObserver{
    public:
    virtual void notifyObservers()=0;
    virtual ~NotifyObserver()=default;
};