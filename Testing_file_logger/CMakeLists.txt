# Тестовое приложение для файлового логгера
add_executable(file_logger_app
    main.cpp
)

# Заголовочные файлы
target_include_directories(file_logger_app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../Functions_for_testing
    ${CMAKE_CURRENT_SOURCE_DIR}/../liblogger
)

# Зависимости
target_link_libraries(file_logger_app
    functions_for_testing
    logger
)

# Копирование скрипта очистки
file(COPY scripts DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})