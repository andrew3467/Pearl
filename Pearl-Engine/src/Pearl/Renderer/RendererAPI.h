//
// Created by Andrew Graser on 2/24/2024.
//

#ifndef PEARL_RENDERERAPI_H
#define PEARL_RENDERERAPI_H

#include "glm/vec4.hpp"
#include "VertexArray.h"

#include <memory>


namespace Pearl {
    class RendererAPI {
    public:
        enum class API {
            None = 0,
            OpenGL = 1
        };


    public:
        virtual void Init() = 0;

        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void SetViewport(uint32_t x, uint32_t y,uint32_t width, uint32_t height) = 0;

        virtual void Clear() = 0;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

        inline static API GetAPI() {return sAPI;}

    private:
        static API sAPI;
    };
}

#endif //PEARL_RENDERERAPI_H
