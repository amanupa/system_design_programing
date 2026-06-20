#include <iostream>
#include "toppins_decorator.h"
#include "../base_pizza.h"

class ExtraCheese : public PizzaToppins{
    private:
    BasePizza* basepizza;
    public:
    ExtraCheese(BasePizza* basepizza){
        this->basepizza=basepizza;
    }
    int cost()override{
        return this->basepizza->cost()+10;
    }

    virtual ~ExtraCheese()=default;


};