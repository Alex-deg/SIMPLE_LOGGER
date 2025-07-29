#include "Logger.h"

Logger::Logger(const std::string &path, Levels level){

    log_file.open(path, std::ios::in | std::ios::out);
    if(!log_file.is_open()){
        std::cout << "Файл не открыт" << std::endl;
        throw std::invalid_argument("File doesn't exist");
    }

}

Logger::~Logger(){
    log_file.close();
}

std::string Logger::now() {
    // Получаем текущее время
    auto now = std::chrono::system_clock::now();
    
    // Конвертируем в локальное время (с учетом часового пояса)
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    auto now_tm = *std::localtime(&now_time_t);  // Для UTC используйте std::gmtime
    
    // Форматируем в строку ЧЧ:ММ:СС
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%H:%M:%S");
    
    return oss.str();
}
