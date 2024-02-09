cmake_minimum_required(VERSION 3.27)
project(Pearl-Engine)

set(CMAKE_CXX_STANDARD 23)



# SPDLOG
add_subdirectory(external/spdlog)
include_directories(external/spdlog/include)

#GLFW
add_subdirectory(external/glfw)
include_directories(external/glfw/include)

#GLAD
include_directories(external/glad/include)
set(GLAD_SRC external/glad/src/glad.c
        src/Pearl/Layer.cpp
        src/Pearl/Layer.h
        src/Pearl/LayerStack.cpp
        src/Pearl/LayerStack.h)



include_directories(src)



#Tell glfw not to include OpenGL
add_compile_definitions(GLFW_INCLUDE_NONE)


file(GLOB_RECURSE SOURCE *.cpp)
file(GLOB_RECURSE HEADERS *.h)


add_library(Pearl-Engine
        ${SOURCE}
        ${HEADERS}
        ${GLAD_SRC}
)

target_link_libraries(Pearl-Engine
        PUBLIC
        spdlog::spdlog
        glfw
)
