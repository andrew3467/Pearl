//
// Created by Andrew Graser on 2/24/2024.
//

#ifndef PEARL_OPENGLRENDERERAPI_H
#define PEARL_OPENGLRENDERERAPI_H

#include "Pearl/Renderer/RendererAPI.h"

namespace Pearl {
    class OpenGLRendererAPI : public RendererAPI {
    public:
        virtual void Init() override;

        virtual void SetClearColor(const glm::vec4& color) override;
        virtual void Clear() override;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

    private:
    };
}


#endif //PEARL_OPENGLRENDERERAPI_H
