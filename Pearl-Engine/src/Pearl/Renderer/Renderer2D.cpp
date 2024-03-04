//
// Created by Andrew Graser on 3/1/2024.
//

#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "glm/ext/matrix_transform.hpp"
#include "RenderCommand.h"


namespace Pearl {

    struct Renderer2DStorage {
        Ref<VertexArray> QuadVA;
        Ref<Shader> SolidUnlitShader;
        Ref<Shader> TextureShader;
    };

    static Renderer2DStorage *sData;

    void Renderer2D::Init() {
        sData = new Renderer2DStorage();

        sData->QuadVA = Pearl::VertexArray::Create();

        float squareVertices[4 * 3 * 2] = {
                -0.5f, -0.5f, 0.0f,         0.0f, 0.0f,
                0.5f, -0.5f, 0.0f,          1.0f, 0.0f,
                0.5f, 0.5f, 0.0f,        1.0f, 1.0f,
                -0.5f, 0.5f, 0.0f,       0.0f, 1.0f,
        };

        uint32_t squareIndices[6] = {
                0, 1, 2,
                2, 3, 0
        };

        std::shared_ptr<Pearl::VertexBuffer> squareVB;
        squareVB.reset(Pearl::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        squareVB->SetLayout({
                                    {Pearl::ShaderDataType::Float3, "aPosition"},
                                    {Pearl::ShaderDataType::Float2, "aTexCoord"},
                            });
        sData->QuadVA->AddVertexBuffer(squareVB);

        std::shared_ptr<Pearl::IndexBuffer> squareIB;
        squareIB.reset((Pearl::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t))));
        sData->QuadVA->SetIndexBuffer(squareIB);


        sData->SolidUnlitShader = Pearl::Shader::Create("../../assets/shaders/Solid_Unlit.glsl");
        sData->TextureShader = Pearl::Shader::Create("../../assets/shaders/Texture.glsl");
    }

    void Renderer2D::Shutdown() {
        delete sData;
    }

    void Renderer2D::BeginScene(const OrthographicCamera &camera) {
        sData->SolidUnlitShader->Bind();
        sData->SolidUnlitShader->SetMat4("uViewProjection", camera.GetViewProjectionMatrix());

        sData->TextureShader->Bind();
        sData->TextureShader->SetMat4("uViewProjection", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::EndScene() {

    }

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color, float rotation) {
        DrawQuad(glm::vec3(position.x, position.y, 0.0f), size, color, rotation);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color, float rotation) {
        auto transform = glm::rotate(glm::scale(glm::translate(glm::mat4(1.0f),
                                                               glm::vec3(position.x, position.y, 0.0f)),
                                                glm::vec3(size.x, size.y, 1.0f)),
                                     glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));

        sData->SolidUnlitShader->Bind();
        sData->SolidUnlitShader->SetMat4("uTransform", transform);
        sData->SolidUnlitShader->SetFloat4("uColor", color);

        sData->QuadVA->Bind();
        RenderCommand::DrawIndexed(sData->QuadVA);

    }

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> texture, float rotation) {
        DrawQuad(glm::vec3(position.x, position.y, 0.0f), size, texture, rotation);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> texture, float rotation) {
        auto transform = glm::rotate(glm::scale(glm::translate(glm::mat4(1.0f),
                                                               glm::vec3(position.x, position.y, 0.0f)),
                                                glm::vec3(size.x, size.y, 1.0f)),
                                     glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));

        sData->TextureShader->Bind();
        sData->TextureShader->SetMat4("uTransform", transform);

        texture->Bind();
        sData->TextureShader->SetInt("uTexture", 0);

        sData->QuadVA->Bind();
        RenderCommand::DrawIndexed(sData->QuadVA);
    }
}