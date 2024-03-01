//
// Created by Andrew Graser on 2/5/2024.
//

#ifndef PEARL_APPLICATION_H
#define PEARL_APPLICATION_H

#include <memory>
#include "Pearl/Core/Core.h"
#include "Pearl/Core/Window.h"
#include "Pearl/Events/ApplicationEvent.h"
#include "Pearl/Core/LayerStack.h"
#include "Pearl/ImGui/ImGuiLayer.h"
#include "Pearl/Renderer/Shader.h"
#include "Pearl/Renderer/VertexArray.h"
#include "Pearl/Renderer/OrthographicCamera.h"
#include "../../../../Tungsten/Wolframite/src/Wolframite/Core/Timestep.h"


namespace Pearl {
    class Application {
    public:
        Application();
        ~Application();

        void Run();

        void OnEvent(Event &e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        inline static Application& Get() {return *sInstance;}
        inline Window& GetWindow() {return *mWindow;}

    private:
        bool OnWindowClosed(WindowCloseEvent &e);

    private:

        static Application *sInstance;

    private:

        std::unique_ptr<Window> mWindow;
        ImGuiLayer* mImGuiLayer;

        bool mRunning = true;
        LayerStack mLayerStack;

        float mLastFrameTime = 0.0f;
    };

    Application* CreateApplication();   //Defined in client
}


#endif //PEARL_APPLICATION_H
