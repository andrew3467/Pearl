//
// Created by Andrew Graser on 2/5/2024.
//

#ifndef PEARL_APPLICATION_H
#define PEARL_APPLICATION_H

#include <Core.h>


namespace Pearl {
    class Application {
    public:
        Application();
        ~Application();

        void Run();
    };

    Application* CreateApplication();   //Defined in client
}


#endif //PEARL_APPLICATION_H
