//
// Created by Andrew Graser on 2/17/2024.
//

#ifndef PEARL_OPENGLCONTEXT_H
#define PEARL_OPENGLCONTEXT_H

#include "Pearl/Renderer/GraphicsContext.h"


struct GLFWwindow;

namespace Pearl {
    class OpenGLContext : public GraphicsContext {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

    public:
        virtual void Init() override;
        virtual void SwapBuffers() override;

    private:
        GLFWwindow* mWindowHandle;
    };
}


#endif //PEARL_OPENGLCONTEXT_H
