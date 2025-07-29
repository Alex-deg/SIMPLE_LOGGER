#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>

enum Levels {DEBUG, INFO, WARNING, ERROR, FATAL};

class Logger{

public:
    Logger(const std::string &path, Levels level);
    ~Logger();

    void debug(const std::string &message);
    void info(const std::string &message);
    void warning(const std::string &message);
    void error(const std::string &message);
    void fatal(const std::string &message);

private:

    std::string now();

    Levels _level;
    std::fstream log_file;
};