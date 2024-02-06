cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 23)

project(Pearl)

add_subdirectory(Pearl-Engine)

include_directories(Pearl-Engine)
include_directories(Pearl-Engine/src)

add_executable(Pearl main.cpp)


target_link_libraries(Pearl
        PUBLIC
        Pearl-Engine
)