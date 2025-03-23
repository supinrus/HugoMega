cmake_minimum_required(VERSION 3.10)
project(hugomain)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall")

find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME} hugomain.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions("-g -O0 -Wall -Wextra -Wpedantic -fsanitize=address")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
endif ()

target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})

# Debug build option
set(CMAKE_BUILD_TYPE Debug)
