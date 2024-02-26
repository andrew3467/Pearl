//
// Created by Andrew Graser on 2/5/2024.
//

#include "Application.h"
#include "Log.h"

#include "Pearl/Input.h"
#include "Pearl/Renderer/Renderer.h"
#include "Pearl/Renderer/RenderCommand.h"



namespace Pearl {
#define BIND_EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)

    Application* Application::sInstance = nullptr;


    Application::Application() {
        Pearl::Log::Init();

        PRL_ASSERT(!sInstance, "Only 1 Application instance may exist")
        sInstance = this;

        mWindow = std::unique_ptr<Window>(Window::Create());
        mWindow->SetEventCallback(BIND_EVENT_FUNC(Application::OnEvent));

        mImGuiLayer = new ImGuiLayer();
        PushOverlay(mImGuiLayer);

    }

    Application::~Application() {

    }


    void Application::Run() {
        while(mRunning){
            for(Layer* layer : mLayerStack){
                layer->OnUpdate();
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