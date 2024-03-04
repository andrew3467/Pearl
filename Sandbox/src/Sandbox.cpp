//
// Created by Andrew Graser on 3/2/2024.
//

#include <Pearl/Core/EntryPoint.h>

#include "Sandbox2D.h"

class Sandbox : public Pearl::Application{
public:
    Sandbox() {
        PushLayer(new Sandbox2D());
    }
    ~Sandbox() {

    }
};

Pearl::Application* Pearl::CreateApplication(){
    return new Sandbox();
}
