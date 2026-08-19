cmake_minimum_required(VERSION 3.5)

project(db1-lib
    VERSION 0.1
    DESCRIPTION "Static library with classes that allow you to work with the database"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SQLite3 3.47.0 REQUIRED)

#Для корректного поиска файлов FindXXX.cmake добавляем директорию сборки в MODULE_PATH
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB db-src "include/*.h" "*.cpp")

add_library(${PROJECT_NAME} STATIC ${db-src})

target_link_libraries(${PROJECT_NAME} PUBLIC 
    SQLite::SQLite3
)

include_directories(${SQLite3_INCLUDE_DIRS})

target_include_directories(${PROJECT_NAME} PUBLIC include)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
