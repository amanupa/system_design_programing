#pragma once
#include "log_proccessor.h"
#include<iostream>
#include <memory>
using namespace std;

class DebugLogger : public LogProcessor{
    public:
    DebugLogger(unique_ptr<LogProcessor> next):LogProcessor(move(next)){}

    void log(int level, string message)override{
        if(level== LogProcessor::DEBUG){
            cout<<"DEBUG: "<<message<<endl;
        }else{
            LogProcessor::log(level,message);
        }
    }
    virtual ~DebugLogger()=default;
};