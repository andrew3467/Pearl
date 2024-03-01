cmake_minimum_required(VERSION 3.27)
project(Pearl-Engine)

set(CMAKE_CXX_STANDARD 23)



#SPDLog
add_subdirectory(external/spdlog)
include_directories(external/spdlog/include)

#GLAD
file(GLOB_RECURSE GLAD_SRC external/glad/*)
include_directories(external/glad/include)

#GLFW
add_subdirectory(external/glfw)
include_directories(external/glfw/include)


#Imgui
add_subdirectory(external/imgui)
include_directories(external/imgui)

#stb image
file(GLOB_RECURSE STB_SRC external/stbimage/*)
include_directories(external/stbimage/include)



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
        ImGui
)

target_include_directories(Pearl-Engine
        PUBLIC
        src
        external/glm
)
