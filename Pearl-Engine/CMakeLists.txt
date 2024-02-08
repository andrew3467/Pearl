cmake_minimum_required(VERSION 3.27)
project(Pearl-Engine)

set(CMAKE_CXX_STANDARD 23)



# SPDLOG
add_subdirectory(external/spdlog)
include_directories(external/spdlog/include)



include_directories(src)


file(GLOB_RECURSE SOURCE *.cpp)
file(GLOB_RECURSE HEADERS *.h)


add_library(Pearl-Engine
        ${SOURCE}
        ${HEADERS}
)

target_link_libraries(Pearl-Engine
        PUBLIC
        spdlog::spdlog
)
