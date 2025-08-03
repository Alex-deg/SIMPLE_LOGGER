# Клиент для отправки логов через сокет
add_executable(socket_client_app
    sending_main.cpp
)

# Заголовочные файлы
target_include_directories(socket_client_app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../Functions_for_testing
    ${CMAKE_CURRENT_SOURCE_DIR}/../../liblogger
)

# Зависимости - ИЗМЕНЕНО!
target_link_libraries(socket_client_app
    functions_for_testing
    logger
    ${CMAKE_THREAD_LIBS_INIT}  # Вместо Threads::Threads
)