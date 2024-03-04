//
// Created by Andrew Graser on 2/20/2024.
//

#include "Renderer.h"
#include "RenderCommand.h"
#include "Pearl/Platform/OpenGL/OpenGLShader.h"
#include "Renderer2D.h"

namespace Pearl {

    Renderer::SceneData* Renderer::mSceneData = new Renderer::SceneData;

    void Renderer::BeginScene(OrthographicCamera &camera) {
        mSceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene() {

    }

    void Renderer::Submit(const std::shared_ptr<Shader> &shader, std::shared_ptr<VertexArray> &vertexArray, const glm::mat4& transform) {
        shader->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->SetMat4("uViewProjection", mSceneData->ViewProjectionMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->SetMat4("uTransform", transform);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

    void Renderer::Init() {
        RenderCommand::Init();

        Renderer2D::Init();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
        RenderCommand::SetViewport(0, 0, width, height);
    }
}