cmake_minimum_required(VERSION 3.5)

project(CPP-DB-module
    DESCRIPTION "Examples of different approaches to working with a database in C++"
    HOMEPAGE_URL "https://github.com/STyulenev/CPP-DB-module"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

set(PROJECT_SOURCES
    main.cpp
)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    db1-lib
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
