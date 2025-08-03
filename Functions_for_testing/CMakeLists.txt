# Вспомогательные функции для тестовых приложений
add_library(functions_for_testing
    functions.cpp
)

# Заголовочные файлы
target_include_directories(functions_for_testing PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Зависимости
target_link_libraries(functions_for_testing PUBLIC logger)