# Библиотека статистики
add_library(statistics
    statistic.cpp
)

# Заголовочные файлы
target_include_directories(statistics PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)