#include <iostream>
#include "base_pizza.h"

class FarmHouse : public BasePizza{
    public:
    int cost() override{
        return 300;
    }

    virtual ~FarmHouse()=default;
};