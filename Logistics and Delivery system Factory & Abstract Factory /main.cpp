#include "factory/Logistic_Factory/logistic.h"
#include "factory/Logistic_Factory/road_logistic.h"
#include "factory/Logistic_Factory/sea_logistic.h"
#include <iostream>
using namespace std;

void handleLogistic(const ILogistic& logistic){
    logistic.planDelivery();
}

int main(){
    cout<<"App: Launching road logistic: "<<endl;
    RoadLogidtic roadlogistic;
    handleLogistic(roadlogistic);

    cout<<"App: Launching sea logistic: "<<endl;
    SeaLogistic sealogistic;
    handleLogistic(sealogistic);

    return 0;
}