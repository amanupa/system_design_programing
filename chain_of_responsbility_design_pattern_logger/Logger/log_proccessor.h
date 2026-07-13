#pragma once 
#include <iostream>
#include <memory>
using namespace std;

class LogProcessor{
    private:
    unique_ptr<LogProcessor> nextLogProcessor;
    public:
    static const int INFO=1;
    static const int DEBUG=2;
    static const int ERROR=3;
    LogProcessor(unique_ptr<LogProcessor> next):nextLogProcessor(move(next)){}
    virtual void log(int level, string message){
        if(nextLogProcessor!= nullptr){
            nextLogProcessor->log(level,message);
        }
    }

    virtual ~LogProcessor()=default;
};