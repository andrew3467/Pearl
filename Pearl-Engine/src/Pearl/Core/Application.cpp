//
// Created by Andrew Graser on 2/5/2024.
//

#include "Application.h"
#include "Pearl/Core/Log.h"

#include "Pearl/Core/Input.h"
#include "Pearl/Renderer/Renderer.h"

#include "GLFW/glfw3.h"


namespace Pearl {
#define BIND_EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)

    Application* Application::sInstance = nullptr;


    Application::Application() {
        Pearl::Log::Init();

        PRL_ASSERT(!sInstance, "Only 1 Application instance may exist")
        sInstance = this;

        mWindow = std::unique_ptr<Window>(Window::Create());
        mWindow->SetEventCallback(BIND_EVENT_FUNC(Application::OnEvent));

        Renderer::Init();

        mImGuiLayer = new ImGuiLayer();
        PushOverlay(mImGuiLayer);

    }

    Application::~Application() {

    }


    void Application::Run() {
        while(mRunning){
            float time = (float)glfwGetTime();     //Platform::GetTime()
            Timestep timestep = time - mLastFrameTime;
            mLastFrameTime = time;

            if(!mMinimized) {
                for (Layer *layer: mLayerStack) {
                    layer->OnUpdate(timestep);
                }
            }

            mImGuiLayer->Begin();
            for(Layer* layer : mLayerStack){
                layer->OnImGuiRender();
            }
            mImGuiLayer->End();

            mWindow->OnUpdate();
        }
    }

    void Application::OnEvent(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Application::OnWindowClosed));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNC(Application::OnWindowResize));

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

    bool Application::OnWindowResize(Pearl::WindowResizeEvent &e) {
        if(e.GetHeight() == 0 || e.GetWidth() == 0){
            mMinimized = true;
            return false;
        }

        mMinimized = false;

        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

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