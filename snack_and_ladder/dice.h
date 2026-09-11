#pragma once
#include<iostream>
#include<random>
using namespace std;

class Dice{
    private:
    int countOfDice;
    public:
    Dice(int count):countOfDice(count){}
    int rollDice() {
    static std::random_device rd;   
    static std::mt19937 gen(rd());  
    std::uniform_int_distribution<int> distrib(1, 6); 

    return (countOfDice* distrib(gen)); 
    }
    virtual ~Dice()=default;
};