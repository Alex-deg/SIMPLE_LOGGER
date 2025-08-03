#include "../../Functions_for_testing/functions.h"

int main(int argc, char* argv[]) {

    try{
        auto settings = parse_command_line_socketlog(argc, argv); // получаем настройки из командной строки
        std::shared_ptr<SocketLogger> socket_log = std::make_shared<SocketLogger>(settings.first, settings.second);
        start_testing(socket_log); // ручное тестирование 
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

}