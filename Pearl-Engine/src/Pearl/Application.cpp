//
// Created by Andrew Graser on 2/5/2024.
//

#include "Application.h"
#include "Log.h"

#include "Pearl/Input.h"

#include <GLFW/glfw3.h>
#include <Glad/glad.h>

namespace Pearl {
#define BIND_EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)

    Application* Application::sInstance = nullptr;

    Application::Application() {
        PRL_ASSERT(sInstance == nullptr, "Only 1 Application instance may exist")
        sInstance = this;

        mWindow = std::unique_ptr<Window>(Window::Create());
        mWindow->SetEventCallback(BIND_EVENT_FUNC(Application::OnEvent));
    }

    Application::~Application() {

    }


    void Application::Run() {
        Pearl::Log::Init();

        while(mRunning){
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);


            for(Layer* layer : mLayerStack){
                layer->OnUpdate();
            }

            mWindow->OnUpdate();
        }
    }

    void Application::OnEvent(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Application::OnWindowClosed));

        for(auto it = mLayerStack.end(); it != mLayerStack.begin(); ){
            (*--it)->OnEvent(e);
            if(e.Handled){
                break;
            }
        }
    }

    bool Application::OnWindowClosed(WindowCloseEvent &e) {
        mRunning = false;

        return true;
    }

    void Application::PushLayer(Layer *layer) {
        mLayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *overlay) {
        mLayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }
}