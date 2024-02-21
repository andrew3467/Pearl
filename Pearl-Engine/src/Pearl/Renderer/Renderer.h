//
// Created by Andrew Graser on 2/20/2024.
//

#ifndef PEARL_RENDERER_H
#define PEARL_RENDERER_H


namespace Pearl {
    enum class RendererAPI {
        None = 0,
        OpenGL = 1
    };

    class Renderer {
    public:
        static inline RendererAPI GetAPI() { return sRendererAPI; }

    private:
        static RendererAPI sRendererAPI;
    };
}


#endif //PEARL_RENDERER_H
