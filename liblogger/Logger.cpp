#include "Logger.h"

Logger::Logger(const std::string &path, Levels level) : _level(level){

    log_file.open(path, std::ios::app);
    if(!log_file.is_open()){
        std::cout << "Файл не открыт" << std::endl;
        throw std::invalid_argument("File doesn't exist");
    }

}

Logger::~Logger(){
    log_file.close();
}

void Logger::debug(const std::string &message){
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

std::string Logger::now() {
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    auto now_tm = *std::localtime(&now_time_t); 
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void Logger::write_log(const std::string &message){
    log_file << message + '\n';
}
