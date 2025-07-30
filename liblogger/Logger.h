#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>

namespace log {

enum Levels {DEBUG, INFO, WARNING, ERROR, FATAL};       // уровни логирования

class ILogger{
public:
    void virtual debug(const std::string &message)     = 0; // запись лога с уровнем debug
    void virtual info(const std::string &message)      = 0; // запись лога с уровнем info
    void virtual warning(const std::string &message)   = 0; // запись лога с уровнем warning
    void virtual error(const std::string &message)     = 0; // запись лога с уровнем error
    void virtual fatal(const std::string &message)     = 0; // запись лога с уровнем fatal
    void virtual set_level(Levels level)               = 0; // сеттер для текущего уровня логирования 
                                                            // (сообщения с уровнем логирования < чем текущий
                                                            // не записываются)
    std::string virtual now()                          = 0;
    void virtual write_log(const std::string &message) = 0;
};

class Logger : public ILogger {
public:
    Logger(Levels level = Levels::INFO);
    void debug(const std::string &message) override;
    void info(const std::string &message) override;
    void warning(const std::string &message) override;
    void error(const std::string &message) override;
    void fatal(const std::string &message) override;
    void set_level(Levels level) override;
protected:
    std::string virtual now() override;
    void virtual write_log(const std::string &message) override;
    Levels _level;
};

class FileLogger : public Logger{
public:
    FileLogger(const std::string &path, Levels level = Levels::INFO);
    
};

}