//
// Created by Andrew Graser on 2/5/2024.
//

#ifndef PEARL_APPLICATION_H
#define PEARL_APPLICATION_H

#include <memory>
#include "Core.h"
#include "Window.h"
#include "Pearl/Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Pearl/ImGui/ImGuiLayer.h"
#include "Pearl/Renderer/Shader.h"
#include "Pearl/Renderer/Buffer.h"


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

        static Application *sInstance;

        std::unique_ptr<Window> mWindow;
        ImGuiLayer* mImGuiLayer;

        bool mRunning = true;
        LayerStack mLayerStack;

        unsigned int mVertexArray;
        std::unique_ptr<Shader> mShader;
        std::unique_ptr<VertexBuffer> mVertexBuffer;
        std::unique_ptr<IndexBuffer> mIndexBuffer;
    };

    Application* CreateApplication();   //Defined in client
}


#endif //PEARL_APPLICATION_H
