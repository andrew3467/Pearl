//
// Created by Andrew Graser on 2/17/2024.
//

#include "OpenGLContext.h"

#include "Pearl/Log.h"
#include "Pearl/Core.h"

#include <GLFW/glfw3.h>
#include <Glad/glad.h>


namespace Pearl {

    OpenGLContext::OpenGLContext(GLFWwindow *windowHandle) : mWindowHandle(windowHandle) {
        PRL_CORE_ASSERT(windowHandle, "Window handle is null!");
    }

    void OpenGLContext::Init() {
        glfwMakeContextCurrent(mWindowHandle);
        int success = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        PRL_CORE_ASSERT(success, "Failed to inialize GLAD");

        PRL_CORE_INFO("OpenGL Info:");
        PRL_CORE_INFO(" Vendor: {0}", (const char*)glGetString(GL_VENDOR));
        PRL_CORE_INFO(" Renderer: {0}", (const char*)glGetString(GL_RENDERER));
        PRL_CORE_INFO(" Version: {0}", (const char*)glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers() {
        glfwSwapBuffers(mWindowHandle);
    }
}