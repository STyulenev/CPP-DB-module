cmake_minimum_required(VERSION 3.5)

project(utility-lib
    VERSION 0.1
    DESCRIPTION "Static library with useful functions to simplify working with the database"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB utility-src "include/*.h" "*.cpp")

add_library(${PROJECT_NAME} STATIC ${utility-src})

target_include_directories(${PROJECT_NAME} PUBLIC include)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
