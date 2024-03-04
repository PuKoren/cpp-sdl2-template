cmake_minimum_required(VERSION 3.12)

project(SDL2Template)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIRS})

FetchContent_Declare(
    fetch_vk_bootstrap
    GIT_REPOSITORY https://github.com/charles-lunarg/vk-bootstrap
    GIT_TAG        534e8bb76c695e0db2a8e2f2a222ade65edd900e
)
FetchContent_MakeAvailable(fetch_vk_bootstrap)

file(GLOB SRC_HEADERS_FILES src/*.cpp headers/*.h)

add_executable(SDL2Template ${SRC_HEADERS_FILES})

target_link_libraries(SDL2Template ${SDL2_LIBRARIES} ${Vulkan_LIBRARIES} vk-bootstrap::vk-bootstrap)

target_include_directories(SDL2Template PRIVATE headers)
