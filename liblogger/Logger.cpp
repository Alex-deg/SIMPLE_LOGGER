#include "Logger.h"

using namespace log;

Logger::Logger(Levels level) : _level(level) {}

void Logger::debug(const std::string &message)
{
    if(_level <= Levels::DEBUG)
        write_log(now() + " [ debug ] " + message);
}

void Logger::info(const std::string &message){
    if(_level < Levels::INFO)
        write_log(now() + " [ info ] " + message);
}

void Logger::warning(const std::string &message){
    if(_level < Levels::WARNING)
        write_log(now() + " [ warning ] " + message);
}

void Logger::error(const std::string &message){
    if(_level <= Levels::ERROR)
        write_log(now() + " [ error ] " + message);
}

void Logger::fatal(const std::string &message){
    write_log(now() + " [ fatal ] " + message);
}

void Logger::set_level(Levels level){
    _level = level;
}

std::string Logger::now()
{
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    auto now_tm = *std::localtime(&now_time_t); 
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void Logger::write_log(const std::string &message){
    std::cout << message << std::endl;
}

FileLogger::FileLogger(const std::string &path, Levels level) : Logger(level) {
    std::cout << "Открыть файл" << std::endl;
}
