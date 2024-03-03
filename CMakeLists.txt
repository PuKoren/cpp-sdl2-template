cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

project(SDL2Template)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB SRC_HEADERS_FILES src/*.cpp headers/*.h)

add_executable(SDL2Template ${SRC_HEADERS_FILES})
target_link_libraries(SDL2Template ${SDL2_LIBRARIES})

target_include_directories(SDL2Template PRIVATE headers)
