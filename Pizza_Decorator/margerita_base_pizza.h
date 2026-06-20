#include <iostream>
#include "base_pizza.h"

class Margerita : public BasePizza{
    public:
    int cost() override{
        return 200;
    }

    virtual ~Margerita()=default;
};