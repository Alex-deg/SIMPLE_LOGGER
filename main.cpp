#include <iostream>

#include "liblogger/Logger.h"

int main(){
    Logger logger("../my_prog.log", Logger::DEBUG);
    
    int i = 0;
    logger.debug("Цикл while запущен");
    while(true){
        i++;
        if(i > 1000)
            break;
    }
    logger.debug("Цикл while закончен");
    return 0;
}