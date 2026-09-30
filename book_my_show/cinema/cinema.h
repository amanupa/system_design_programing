#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<memory>
using namespace std;

#include "../screen/screen.h"


class Cinema{
    private:
    int id;
    string name;
    vector<unique_ptr<Screen>>screens;
    public:
    Cinema(int id, string name):id(id),name(name){}

    void addScreen(Screen& screen){
        screens.push_back(make_unique<Screen>(std::move(screen)));
    }

    const vector<unique_ptr<Screen>>& getAllScreen()const{
        return screens;
    }

    Screen& getScreen(int id) const{
        for(auto &screen: screens){
            if(screen->getScreenId()==id){
                return *screen;
            }
        }
        throw runtime_error("screen not found");
    }

    string getCinemaname()const{
        return name;
    }

    int getCinemaId()const{
        return id;
    }

    Cinema(Cinema&&) = default;
    Cinema& operator=(Cinema&&) = default;
    virtual ~Cinema()=default;

};