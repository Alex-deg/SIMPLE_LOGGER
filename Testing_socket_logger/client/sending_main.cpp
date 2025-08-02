#include "../../Functions_for_testing/functions.h"

int main(int argc, char* argv[]) {

    auto settings = parse_command_line_socketlog(argc, argv);

    std::shared_ptr<SocketLogger> socket_log = std::make_shared<SocketLogger>(settings.first, settings.second);

    start_testing(socket_log);

}