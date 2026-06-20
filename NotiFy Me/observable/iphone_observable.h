#pragma once
#include<vector>
#include<iostream>
#include "stock_observable.h"              
#include "../observer/notify_observer.h"
using namespace std;


class IphoneObservable : public StockObservable{
    private:
    vector<NotifyObserver*> notifyObservers;
    int stockCount;
    public:
    IphoneObservable():stockCount(0){}
    void addObservers(NotifyObserver* observer) override{
        notifyObservers.push_back(observer);


    }

    void removeObserver(NotifyObserver* observer) override{
        notifyObservers.erase(remove(notifyObservers.begin(),notifyObservers.end(),observer),
    notifyObservers.end());
    }

    void notify() override{
        for(NotifyObserver* obj : notifyObservers){
            obj->notifyObservers();
        }
    }

    void updateStock(int stock){
        if(stockCount==0){
            notify();
        }
        stockCount+=stock;
    }
    int getStock(){
        return stockCount;
    }

};