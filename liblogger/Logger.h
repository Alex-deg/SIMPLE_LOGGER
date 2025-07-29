#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>

class Logger{

public:

    enum Levels {DEBUG, INFO, WARNING, ERROR, FATAL};

    Logger(const std::string &path, Levels level = Levels::INFO);
    ~Logger();

    void debug(const std::string &message);
    void info(const std::string &message);
    void warning(const std::string &message);
    void error(const std::string &message);
    void fatal(const std::string &message);

    void set_level(Levels level);

private:

    std::string now();
    void write_log(const std::string &message);
    Levels _level;
    std::fstream log_file;
};