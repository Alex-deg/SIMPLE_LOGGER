# Сервер для сбора статистики
add_executable(socket_server_app
    reading_main.cpp
    server.cpp
)

# Заголовочные файлы
target_include_directories(socket_server_app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../libstatistics
)

# Зависимости - ИЗМЕНЕНО!
target_link_libraries(socket_server_app
    statistics
    logger
    ${CMAKE_THREAD_LIBS_INIT}  # Вместо Threads::Threads
)