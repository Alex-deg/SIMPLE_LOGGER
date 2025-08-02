#include "Logger.h"

using namespace liblog;

Logger::Logger(Levels level) : _level(level) {}

// Реализация базовой логики логирования
void Logger::debug(const std::string &message)
{
    if(_level <= Levels::DEBUG)
        write_log(now() + " [" + BLUE + "DEBUG" + RESET + "] " + message);
}

void Logger::info(const std::string &message){
    if(_level <= Levels::INFO)
        write_log(now() + " [" + GREEN + "INFO" + RESET + "] " + message);
}

void Logger::warning(const std::string &message){
    if(_level <= Levels::WARNING)
        write_log(now() + " [" + YELLOW + "WARNING" + RESET + "] " + message);
}

void Logger::error(const std::string &message){
    if(_level <= Levels::ERROR)
        write_log(now() + " [" + ORANGE + "ERROR" + RESET + "] " + message);
}

void Logger::fatal(const std::string &message){
    write_log(now() + " [" + RED + "FATAL" + RESET + "] " + message);
}

void Logger::set_level(Levels level){
    _level = level;
}

Levels Logger::get_level()
{
    return _level;
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
    std::cout << message << std::endl; // простой вывод в консоль
}

FileLogger::FileLogger(const std::string &path, Levels level) : Logger(level) {
    log_file.open(path, std::ios::app); // попытка открыть файл
    if(!log_file.is_open()){
        throw std::invalid_argument("File doesn't exist"); 
    }
}

void FileLogger::write_log(const std::string &message){
    log_file << message + '\n'; // вывод лога в файла
}

SocketLogger::SocketLogger(int port, Levels level) : Logger(level), _port(port) {

    // 1. Создание сокета
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        throw std::runtime_error("Ошибка создания сокета");
    }

    // 2. Настройка адреса сервера
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;     // IPv4
    serverAddr.sin_port = htons(_port);  // Порт сервера
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);  // localhost

    // 3. Подключение к серверу
    if (connect(client_socket, (sockaddr*)&serverAddr, sizeof(serverAddr))) {
        close(client_socket);
        throw std::runtime_error("Ошибка подключения");
    }

}

SocketLogger::~SocketLogger() {
    close(client_socket);
}

void SocketLogger::write_log(const std::string &message) {  
    // Запись в сокет
    ssize_t bytes_sent = send(client_socket, message.c_str(), message.size(), 0);
    if (bytes_sent == -1) {
        throw std::runtime_error("Ошибка отправки данных");
    } else {
        std::cout << "Отправлено " << bytes_sent << " байт" << std::endl;
    }

}

// int liblog::SocketLogger::get_client_fd()
// {
//     return client_socket;
// }

int SocketLogger::set_nonblocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    if(flags == -1) return -1;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    return 0;
}
