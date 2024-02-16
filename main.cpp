//
// Created by Andrew Graser on 2/5/2024.
//

#include <Pearl.h>

class ExampleLayer : public Pearl::Layer{
public:
    ExampleLayer()
        : Layer("Example") {

    }

    void OnUpdate() override {
        if(Pearl::Input::IsKeyPressed(PRL_KEY_TAB)){
            PRL_INFO("Tab Key Pressed");
        }
    }

    void OnEvent(Pearl::Event &event) override {
        //PRL_TRACE("{0}", event.ToString());
    }
};

class Sandbox : public Pearl::Application{
public:
    Sandbox() {
        PushLayer(new ExampleLayer);
        PushOverlay(new Pearl::ImGuiLayer);
    }
    ~Sandbox() {

    }
};

Pearl::Application* Pearl::CreateApplication(){
    return new Sandbox();
}
