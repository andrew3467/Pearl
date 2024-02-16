cmake_minimum_required(VERSION 3.27)
project(ImGui)

set(CMAKE_CXX_STANDARD 23)


include_directories(include/ImGui)

file(GLOB SOURCE *.cpp)
file(GLOB HEADERS *.h)


add_library(ImGui
        ${SOURCE}
        ${HEADERS}
)