project(Sandbox)
cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 23)



add_subdirectory(../Pearl ../bin)
include_directories(../Pearl/src)



file(GLOB_RECURSE SRC src/Sandbox/*.cpp)
file(GLOB_RECURSE HEADERS src/Sandbox/*.h)



add_executable(
        Sandbox
        ${SRC}
        ${HEADERS}
)

target_link_libraries(
        Sandbox
        PUBLIC
        Pearl_Engine
)