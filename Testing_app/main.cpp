#include <iostream>
#include <memory>
#include "../liblogger/Logger.h"

using namespace log;

Levels parseStringToLoggerLevel(const std::string &data){
    std::string current = "";
    for(auto &x : data){
        current += tolower(x);
    }
    if(current=="debug")
        return DEBUG;
    if(current=="info")
        return INFO;
    if(current=="warning")
        return WARNING;
    if(current=="error")
        return ERROR;
    if(current=="fatal")
        return FATAL;
    
    throw std::invalid_argument("Неверно указан уровень логирования");
    
}

int main(int argc, char* argv[]) {

    std::string msg;
    Levels level;
    std::shared_ptr<FileLogger> _log;
    switch (argc)
    {
    case 1:
        std::cerr << "Слишком мало аргументов: должно быть минимум 2" << std::endl;
        return EXIT_FAILURE;    
    case 2:
        msg = argv[1];
        _log = std::make_shared<FileLogger>(msg);
        break;
    case 3:
        msg = argv[1];
        level = parseStringToLoggerLevel(argv[2]);
        _log = std::make_shared<FileLogger>(msg, level);
        break;
    }

    _log->set_level(Levels::DEBUG);
    _log->debug("dsijfdsf");
    _log->error("sosal");


}