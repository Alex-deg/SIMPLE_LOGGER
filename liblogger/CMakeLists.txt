cmake_minimum_required(VERSION 3.14)
project(liblog)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Опция для выбора типа библиотеки (по умолчанию - статическая)
option(BUILD_SHARED_LIBS "Build shared library instead of static" OFF)

# Список исходных файлов
set(SOURCES
    Logger.cpp
)

# Список заголовочных файлов
set(HEADERS
    Logger.h
)

# Создаем библиотеку
add_library(logger
    ${SOURCES}
    ${HEADERS}
)

# Устанавливаем свойства библиотеки
target_include_directories(logger
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Для Unix-систем добавляем необходимые библиотеки
if(UNIX)
    target_link_libraries(logger PUBLIC pthread)
endif()

# Установочные пути
install(TARGETS logger
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(FILES ${HEADERS} DESTINATION include/liblog)

# Опционально: экспорт для использования в других проектах
export(TARGETS logger FILE ${CMAKE_BINARY_DIR}/LoggerConfig.cmake)