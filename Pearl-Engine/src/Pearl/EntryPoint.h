//
// Created by Andrew Graser on 2/5/2024.
//

#ifndef PEARL_ENTRYPOINT_H
#define PEARL_ENTRYPOINT_H


#include "Application.h"

extern Pearl::Application* Pearl::CreateApplication();

int main(int argc, char** argv) {
    auto app = Pearl::CreateApplication();
    app->Run();
    delete app;

    return 0;
}

#endif //PEARL_ENTRYPOINT_H
