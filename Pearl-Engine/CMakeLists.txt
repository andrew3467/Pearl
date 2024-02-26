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



#Tell glfw not to include OpenGL
add_compile_definitions(GLFW_INCLUDE_NONE)


file(GLOB_RECURSE SOURCE *.cpp)
file(GLOB_RECURSE HEADERS *.h)


add_library(Pearl-Engine
        ${SOURCE}
        ${HEADERS}
        ${GLAD_SRC}
        src/Pearl/ImGui/ImGuiBuild.cpp
        src/Pearl/Renderer/GraphicsContext.h
        src/Pearl/Platform/OpenGL/OpenGLContext.h
        src/Pearl/Platform/OpenGL/OpenGLContext.cpp
        src/Pearl/Renderer/Shader.cpp
        src/Pearl/Renderer/Shader.h
        src/Pearl/Renderer/Buffer.cpp
        src/Pearl/Renderer/Buffer.h
        src/Pearl/Platform/OpenGL/OpenGLBuffer.cpp
        src/Pearl/Platform/OpenGL/OpenGLBuffer.h
        src/Pearl/Renderer/Renderer.cpp
        src/Pearl/Renderer/Renderer.h
        src/Pearl/Renderer/VertexArray.cpp
        src/Pearl/Renderer/VertexArray.h
        src/Pearl/Platform/OpenGL/OpenGLVertexArray.cpp
        src/Pearl/Platform/OpenGL/OpenGLVertexArray.h
        src/Pearl/Renderer/RendererAPI.h
        src/Pearl/Renderer/RendererAPI.cpp
        src/Pearl/Renderer/RenderCommand.h
        src/Pearl/Renderer/RenderCommand.cpp
        src/Pearl/Platform/OpenGL/OpenGLRendererAPI.cpp
        src/Pearl/Platform/OpenGL/OpenGLRendererAPI.h
        src/Pearl/Renderer/OrthographicCamera.h
        src/Pearl/Renderer/OrthographicCamera.cpp
        src/Pearl/Core/Timestep.h
        src/Pearl/Platform/OpenGL/OpenGLShader.cpp
        src/Pearl/Platform/OpenGL/OpenGLShader.h
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
