//
// Created by Andrew Graser on 2/24/2024.
//

#ifndef PEARL_RENDERCOMMAND_H
#define PEARL_RENDERCOMMAND_H


#include "RendererAPI.h"

namespace Pearl {
    class RenderCommand {
    public:
        inline static void Init(){
            sRendererAPI->Init();
        }

        inline static void SetClearColor(const glm::vec4& color) {
            sRendererAPI->SetClearColor(color);
        }

        inline static void Clear() {
            sRendererAPI->Clear();
        }

        inline static void DrawIndexed(const std::shared_ptr<VertexArray> vertexArray) {
            sRendererAPI->DrawIndexed(vertexArray);
        }

    private:
        static RendererAPI* sRendererAPI;
    };
}


#endif //PEARL_RENDERCOMMAND_H
