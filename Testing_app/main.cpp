#include <iostream>
#include <memory>
#include "../liblogger/Logger.h"

Logger::Levels parseStringToLoggerLevel(const std::string &data){
    std::string current = "";
    for(auto &x : data){
        current += tolower(x);
    }
    if(current=="debug")
        return Logger::DEBUG;
    if(current=="info")
        return Logger::INFO;
    if(current=="warning")
        return Logger::WARNING;
    if(current=="error")
        return Logger::ERROR;
    if(current=="fatal")
        return Logger::FATAL;
    
    throw std::invalid_argument("Неверно указан уровень логирования");
    
}

int main(int argc, char* argv[]) {

    std::string msg;
    Logger::Levels level;
    std::shared_ptr<Logger> log;
    switch (argc)
    {
    case 1:
        std::cerr << "Слишком мало аргументов: должно быть минимум 2" << std::endl;
        return EXIT_FAILURE;    
    case 2:
        msg = argv[1];
        log = std::make_shared<Logger>(msg);
        break;
    case 3:
        msg = argv[1];
        level = parseStringToLoggerLevel(argv[2]);
        log = std::make_shared<Logger>(msg, level);
        break;
    }


}