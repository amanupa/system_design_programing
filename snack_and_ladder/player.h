#pragma once 
#include<iostream>
using namespace std;

class Player{
    private:
    int id;
    int currPosition;
    string name;
    public:
    Player(int id, int position,string name):id(id),currPosition(position),name(name){}
    int getPosition()const{
        return currPosition;
    }
    void setPosition(int newPosition){
        currPosition=newPosition;
    }
    string getPlayerName(){
        return name;
    }
    virtual ~Player()=default;

};