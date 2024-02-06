cmake_minimum_required(VERSION 3.27)
project(Pearl-Engine)

set(CMAKE_CXX_STANDARD 23)

find_package(spdlog CONFIG REQUIRED)

include_directories(src)


file(GLOB_RECURSE SOURCE *.cpp)
file(GLOB_RECURSE HEADERS *.h)


add_library(Pearl-Engine
        ${SOURCE}
        ${HEADERS}
)

target_link_libraries(Pearl-Engine
        PRIVATE
        spdlog::spdlog
)
