project(Pearl_Engine)
cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 23)

include_directories(src)


file(GLOB_RECURSE SRC src/Pearl/*.cpp)
file(GLOB_RECURSE HEADERS src/Pearl/*.h)


add_library(
        Pearl_Engine
        ${SRC}
        ${HEADERS}
)

set_target_properties(Pearl_Engine PROPERTIES LINKER_LANGUAGE CXX)