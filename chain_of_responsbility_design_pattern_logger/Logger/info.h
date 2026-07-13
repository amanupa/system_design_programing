#pragma once
#include "log_proccessor.h"
#include<iostream>
using namespace std;

class InfoLogger : public LogProcessor{
    public:
    InfoLogger(unique_ptr<LogProcessor> next):LogProcessor(move(next)){}

    void log(int level, string message)override{
        if(level== LogProcessor::INFO){
            cout<<"INFO: "<<message<<endl;
        }else{
            LogProcessor::log(level,message);
        }
    }
    virtual ~InfoLogger()=default;
};