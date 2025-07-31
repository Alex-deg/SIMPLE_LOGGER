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

Levels log::Logger::get_level()
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
    std::cout << message << std::endl;
}

FileLogger::FileLogger(const std::string &path, Levels level) : Logger(level) {
    log_file.open(path, std::ios::app);
    if(!log_file.is_open()){
        throw std::invalid_argument("File doesn't exist"); 
    }
}

void log::FileLogger::write_log(const std::string &message){
    log_file << message + '\n';
}

log::SocketLogger::SocketLogger(int port, Levels level) : Logger(level), _port(port) {

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        throw std::runtime_error("Ошибка создания сокета");
    }
    //set_nonblocking();
}

log::SocketLogger::~SocketLogger() {
    close(client_socket);
}

// Мб connect и inet_pton вынести в конструктор

void log::SocketLogger::write_log(const std::string &message) {

    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(_port);
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        close(client_socket);
        throw std::runtime_error("Ошибка преобразования IP-адреса");
    }

    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        close(client_socket);
        throw std::runtime_error("Ошибка подключения");
    }

    ssize_t bytes_sent = send(client_socket, message.c_str(), message.size(), 0);
    if (bytes_sent == -1) {
        throw std::runtime_error("Ошибка отправки данных");
    } else {
        std::cout << "Отправлено " << bytes_sent << " байт" << std::endl;
    }

}

int log::SocketLogger::set_nonblocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    if(flags == -1) return -1;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    return 0;
}
