//
// Created by Andrew Graser on 2/8/2024.
//

#include "WindowsWindow.h"
#include "Pearl/Log.h"

#include <Pearl/Events/KeyEvent.h>
#include <Pearl/Events/MouseEvent.h>
#include <Pearl/Events/ApplicationEvent.h>

#include <Glad/glad.h>


namespace Pearl {
    static bool sGLFWInitialized = false;

    static void GLFWErrorCallback(int error_code, const char* description){
        PRL_CORE_ERROR("GLFW Error: ({0}), {1}", error_code,  description);
    }

    Window* Window::Create(const Pearl::WindowProps &props) {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps &props){
        Init(props);
    }

    WindowsWindow::~WindowsWindow() {
        Shutdown();
    }

    void WindowsWindow::Init(const WindowProps &props) {
        mData.Title = props.Title;
        mData.Width = props.Width;
        mData.Height = props.Height;

        //PRL_CORE_INFO("Creating window {0} ({1} {2})", props.Title, props.Width, props.Height);

        if(!sGLFWInitialized){
            int success = glfwInit();
            PRL_CORE_ASSERT(success, "Could not initialize GLFW");

            glfwSetErrorCallback(GLFWErrorCallback);

            sGLFWInitialized = true;
        }

        mWindow = glfwCreateWindow((int)mData.Width, (int)mData.Height, mData.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(mWindow);

        int success = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        PRL_CORE_ASSERT(success, "Failed to inialize GLAD");

        glfwSetWindowUserPointer(mWindow, &mData);
        SetVSync(true);

        //Set GLFW callbacks
        glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height){
            auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

            data.Width = width;
            data.Height = height;
            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window) {
            auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods) {
            auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action) {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleassedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xoffset, double yoffset){
            auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xoffset, (float)yoffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double xpos, double ypos){
            auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xpos, (float)ypos);
            data.EventCallback(event);
        });
    }

    void WindowsWindow::Shutdown() {
        glfwDestroyWindow(mWindow);
    }

    void WindowsWindow::SetVSync(bool enabled) {
        if(enabled){
            glfwSwapInterval(1);
        }else{
            glfwSwapInterval(0);
        }

        mData.VSync = enabled;
    }

    bool WindowsWindow::IsVSync() const {
        return mData.VSync;
    }

    void WindowsWindow::OnUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(mWindow);
    }
}