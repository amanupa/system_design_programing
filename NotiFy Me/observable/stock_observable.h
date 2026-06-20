#pragma once 
#include "../observer/notify_observer.h"

class StockObservable{
    public:
    virtual void addObservers(NotifyObserver* observer)=0;
    virtual void removeObserver(NotifyObserver* observer)=0;
    virtual void notify()=0;
    virtual ~StockObservable()=default;
};