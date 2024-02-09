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


namespace Pearl {
    class Application {
    public:
        Application();
        ~Application();

        void Run();

        void OnEvent(Event &e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

    private:
        bool OnWindowClosed(WindowCloseEvent &e);

        std::unique_ptr<Window> mWindow;
        bool mRunning = true;

        LayerStack mLayerStack;
    };

    Application* CreateApplication();   //Defined in client
}


#endif //PEARL_APPLICATION_H
