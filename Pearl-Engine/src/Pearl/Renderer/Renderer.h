//
// Created by Andrew Graser on 2/20/2024.
//

#ifndef PEARL_RENDERER_H
#define PEARL_RENDERER_H


#include <memory>
#include "VertexArray.h"
#include "RendererAPI.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Pearl {

    class Renderer {
    public:
        static void Init();

        static void BeginScene(OrthographicCamera &camera);
        static void EndScene();

        static void Submit(const std::shared_ptr<Shader> &shader, std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));


        inline static RendererAPI::API GetAPI() {return RendererAPI::GetAPI();}

    private:
        struct SceneData {
            glm::mat4 ViewProjectionMatrix;
        };

        static SceneData* mSceneData;
    };
}


#endif //PEARL_RENDERER_H
