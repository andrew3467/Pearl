//
// Created by Andrew Graser on 2/5/2024.
//

#include <Pearl.h>

class Sandbox : public Pearl::Application{
public:
    Sandbox() {

    }
    ~Sandbox() {

    }
};

Pearl::Application* Pearl::CreateApplication(){
    return new Sandbox();
}
