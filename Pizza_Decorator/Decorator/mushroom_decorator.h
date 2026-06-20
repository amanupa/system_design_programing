#include <iostream>
#include "toppins_decorator.h"
#include "../base_pizza.h"

class Mushroom : public PizzaToppins{
    private:
    BasePizza* basepizza;
    public:
    Mushroom(BasePizza* basepizza){
        this->basepizza=basepizza;
    }
    int cost()override{
        return this->basepizza->cost()+ 20;
    }

    virtual ~Mushroom()=default;


};