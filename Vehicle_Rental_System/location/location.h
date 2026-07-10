#pragma once
#include "../store/store.h"
#include <vector>
#include <iostream>
#include <memory>
using namespace std;


class Location {

private:
    vector<unique_ptr<Store>> stores;

public:

    void addStore(unique_ptr<Store> store)
    {
        stores.push_back(move(store));
    }


    vector<unique_ptr<Store>>& getStores()
    {
        return stores;
    }

};