#pragma once
#include "log_proccessor.h"
#include<iostream>
using namespace std;

class ErrorLogger : public LogProcessor{
    public:
    ErrorLogger(unique_ptr<LogProcessor> next):LogProcessor(move(next)){}

    void log(int level, string message)override{
        if(level== LogProcessor::ERROR){
            cout<<"Error: "<<message<<endl;
        }else{
            LogProcessor::log(level,message);
        }
    }
    virtual ~ErrorLogger()=default;
};