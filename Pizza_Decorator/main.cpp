#include <iostream>
using namespace std;
#include "base_pizza.h"
#include "Decorator/toppins_decorator.h"
#include "margerita_base_pizza.h"
#include "farm_house_base_pizza.h"
#include "Decorator/extra_cheese_decorator.h"
#include "Decorator/mushroom_decorator.h"

int main(){
    BasePizza* margerita=new Margerita();
    cout<<margerita->cost()<<endl;
    BasePizza* pizza=new Mushroom(new ExtraCheese(new Margerita())); 
    cout<<"Cost of Margerita pizza with extra cheese & Mushroom: "<<pizza->cost()<<endl;
    
    delete margerita;
    delete pizza;
}
