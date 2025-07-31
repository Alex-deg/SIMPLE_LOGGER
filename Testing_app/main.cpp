#include <iostream>
#include <memory>
#include "../liblogger/Logger.h"
#include <thread>
#include <mutex>

using namespace liblog;

std::mutex file_log_mutex;

void cinFlush(){
    std::cin.clear();
    while(std::cin.get() != '\n');
}

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

std::pair<std::string, Levels> parse_command_line(int argc, char* argv[]) {
    std::string path;
    Levels level;
    switch (argc)
    {
    case 1:
        throw std::invalid_argument("Слишком мало аргументов: должно быть минимум 2");
        break;
    case 2:
        path = argv[1];
        break;
    case 3:
        path = argv[1];
        level = parseStringToLoggerLevel(argv[2]);
        break;
    }
    return {path, level};
}

void test_logger_writing(std::shared_ptr<FileLogger> &file_log, const std::string &msg, Levels lvl){
    std::lock_guard<std::mutex> lock(file_log_mutex);
    if(lvl == Levels::DEBUG)
        file_log->debug(msg);
    if(lvl == Levels::INFO)
        file_log->info(msg);
    if(lvl == Levels::WARNING)
        file_log->warning(msg);
    if(lvl == Levels::ERROR)
        file_log->error(msg);
    if(lvl == Levels::FATAL)
        file_log->fatal(msg);
}

int main(int argc, char* argv[]) {

    auto settings = parse_command_line(argc, argv);

    std::shared_ptr<FileLogger> file_log = std::make_shared<FileLogger>(settings.first, settings.second);
    std::shared_ptr<SocketLogger> socket_log = std::make_shared<SocketLogger>(8888, settings.second);

    char menu, menu2;
    std::string msg;
    Levels level;
    do{
        system("clear");
        std::cout << "1. Сделать запись" << std::endl;
        std::cout << "2. Изменить уровень логирования по умолчанию" << std::endl;
        std::cout << "3. Выход" << std::endl;
        std::cin >> menu;
        switch(menu){
        case '1': {
            system("clear");
            std::cout << "Ваше сообщение: " << std::endl;
            cinFlush();
            std::getline(std::cin, msg);
            std::cout << "Хотите указать уровень логирования? Y/n" << std::endl;
            std::cin >> menu2;
            if(menu2 != 'n' && menu2 != 'N'){
                std::cout << "1. DEBUG" << std::endl;
                std::cout << "2. INFO" << std::endl;
                std::cout << "3. WARNING" << std::endl;
                std::cout << "4. ERROR" << std::endl;
                std::cout << "5. FATAL" << std::endl;
                std::cin >> menu2;
                switch(menu2){
                    case '1' : level = Levels::DEBUG; break;
                    case '2' : level = Levels::INFO; break;
                    case '3' : level = Levels::WARNING; break;
                    case '4' : level = Levels::ERROR; break;
                    case '5' : level = Levels::FATAL; break;
                }
            }
            else level = file_log->get_level();
            std::thread handle_data(test_logger_writing, std::ref(file_log), std::cref(msg), level);
            handle_data.join();
            break;
        }
        case '2': {
            std::cout << "1. DEBUG" << std::endl;
            std::cout << "2. INFO" << std::endl;
            std::cout << "3. WARNING" << std::endl;
            std::cout << "4. ERROR" << std::endl;
            std::cout << "5. FATAL" << std::endl;
            std::cin >> menu2;
            switch(menu2){
                case '1' : file_log->set_level(Levels::DEBUG); break;
                case '2' : file_log->set_level(Levels::INFO); break;
                case '3' : file_log->set_level(Levels::WARNING); break;
                case '4' : file_log->set_level(Levels::ERROR); break;
                case '5' : file_log->set_level(Levels::FATAL); break;
            }
            break;
        }
        }
    }while(menu != '3');


}