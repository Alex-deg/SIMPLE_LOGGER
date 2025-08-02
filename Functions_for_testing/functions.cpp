#include "functions.h"

std::mutex log_mutex;

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

std::pair<std::string, Levels> parse_command_line_filelog(int argc, char* argv[]) {
    std::string path;
    Levels level;
    switch (argc)
    {
    case 1:
        throw std::invalid_argument("Слишком мало аргументов: должно быть минимум 2");
        break;
    case 2:
        path = argv[1];                            // получение пути к журналу
        break;
    case 3:
        path = argv[1];                            // получение пути к журналу
        level = parseStringToLoggerLevel(argv[2]); // получение уровня логирования по умолчанию
        break;
    }
    return {path, level};
}

std::pair<int, Levels> parse_command_line_socketlog(int argc, char* argv[]) {
    int port;
    Levels level;
    switch (argc)
    {
    case 1:
        throw std::invalid_argument("Слишком мало аргументов: должно быть минимум 2");
        break;
    case 2:
        port = std::stoi(argv[1]);                 // получение порта, на котором слушаются подключения
        break;
    case 3:
        port = std::stoi(argv[1]);                 // получение порта, на котором слушаются подключения
        level = parseStringToLoggerLevel(argv[2]); // получение уровня логирования по умолчанию
        break;
    }
    return {port, level};
}

void test_logger_writing(std::shared_ptr<Logger> &logger, const std::string &msg, Levels lvl){
    std::lock_guard<std::mutex> lock(log_mutex);
    if(lvl == Levels::DEBUG)
        logger->debug(msg);
    if(lvl == Levels::INFO)
        logger->info(msg);
    if(lvl == Levels::WARNING)
        logger->warning(msg);
    if(lvl == Levels::ERROR)
        logger->error(msg);
    if(lvl == Levels::FATAL)
        logger->fatal(msg);
}

void start_testing(std::shared_ptr<Logger> log) {

    unsigned char menu, menu2; // переменные для сохранения выбора пользователя
    std::string msg;        
    Levels level;
    do{
        system("clear"); // очистка консоли
        std::cout << "1. Сделать запись" << std::endl; // меню, представляющее базовый функционал
        std::cout << "2. Изменить уровень логирования по умолчанию" << std::endl;
        std::cout << "3. Выход" << std::endl;
        std::cin >> menu; // получение ответа от пользователя
        switch(menu){
        case '1': {
            system("clear");
            std::cout << "Ваше сообщение: " << std::endl;
            cinFlush();
            std::getline(std::cin, msg); // получение сообщения от пользователя
            std::cout << "Хотите указать уровень логирования? Y/n" << std::endl;
            std::cin >> menu2;
            if(menu2 != 'n' && menu2 != 'N'){ // если пользователь не говорит явно нет
                                              // предлагается выбрать уровень логирования
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
            else level = log->get_level(); // иначе выбирается уровень по умолчанию
            std::thread handle_data(test_logger_writing, std::ref(log), std::cref(msg), level); // запись лога
            handle_data.join(); 
            break;
        }
        case '2': {
            // присваивание нового значения уровня логирования по умолчанию
            std::cout << "1. DEBUG" << std::endl;
            std::cout << "2. INFO" << std::endl;
            std::cout << "3. WARNING" << std::endl;
            std::cout << "4. ERROR" << std::endl;
            std::cout << "5. FATAL" << std::endl;
            std::cin >> menu2;
            switch(menu2){
                case '1' : log->set_level(Levels::DEBUG); break;
                case '2' : log->set_level(Levels::INFO); break;
                case '3' : log->set_level(Levels::WARNING); break;
                case '4' : log->set_level(Levels::ERROR); break;
                case '5' : log->set_level(Levels::FATAL); break;
            }
            break;
        }
        }
    }while(menu != '3'); // меню крутиться пока пользователь не нажмет 3, т.е. "выход"


}