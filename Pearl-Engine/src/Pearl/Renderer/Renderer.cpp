//
// Created by Andrew Graser on 2/20/2024.
//

#include "Renderer.h"
#include "RenderCommand.h"

namespace Pearl {

    Renderer::SceneData* Renderer::mSceneData = new Renderer::SceneData;

    void Renderer::BeginScene(OrthographicCamera &camera) {
        mSceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene() {

    }

    void Renderer::Submit(const std::shared_ptr<Shader> &shader, std::shared_ptr<VertexArray> &vertexArray) {
        shader->Bind();
        shader->UploadUniformMat4("uViewProjection", mSceneData->ViewProjectionMatrix);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}