#include <iostream>
using namespace std;
#include "Logger/log_proccessor.h"
#include "Logger/info.h"
#include "Logger/debug.h"
#include "Logger/error.h"

int main(){
    unique_ptr<LogProcessor> logObj= make_unique<InfoLogger>( make_unique<DebugLogger>(make_unique <ErrorLogger>(nullptr)));
    logObj->log(LogProcessor::INFO,"info logger");
    logObj->log(LogProcessor::ERROR,"error logger");
    logObj->log(LogProcessor::DEBUG,"Debug logger");
}