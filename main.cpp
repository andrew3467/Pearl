//
// Created by Andrew Graser on 2/5/2024.
//

#include <Pearl.h>

#include <imgui.h>
#include "glm/gtc/matrix_transform.hpp"
#include "Pearl/Platform/OpenGL/OpenGLShader.h"
#include "glm/gtc/type_ptr.hpp"



class ExampleLayer : public Pearl::Layer{
public:
    ExampleLayer()
        : Layer("Example"), mCameraController(1280.0f / 720.0f, true) {
        mSquareVA.reset(Pearl::VertexArray::Create());

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
        mSquareVA->AddVertexBuffer(squareVB);

        std::shared_ptr<Pearl::IndexBuffer> squareIB;
        squareIB.reset((Pearl::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t))));
        mSquareVA->SetIndexBuffer(squareIB);


        mShaderLibrary.Load("../assets/shaders/Solid_Unlit.glsl", "Solid Unlit");
        mShaderLibrary.Load("../assets/shaders/Texture.glsl");


        mTexture = Pearl::Texture2D::Create("../assets/textures/Checkerboard.png");
        mChernoLogoTexture = Pearl::Texture2D::Create("../assets/textures/ChernoLogo.png");

        std::dynamic_pointer_cast<Pearl::OpenGLShader>(mShaderLibrary.Get("Texture"))->UploadUniformInt("uTexture", 0);
    }

    void OnUpdate(Pearl::Timestep ts) override {
        mCameraController.OnUpdate(ts);

        Pearl::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Pearl::RenderCommand::Clear();

        Pearl::Renderer::BeginScene(mCameraController.GetCamera());


        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));


        auto textureShader = mShaderLibrary.Get("Texture");
        auto solidShader = mShaderLibrary.Get("Solid Unlit");

        solidShader->Bind();
        for(int y = 0; y < mNumCols; y++){
            for (int x = 0; x < mNumRows; ++x) {
                glm::vec3 pos((x - mNumRows / 2.0f) * 0.11f, (y - mNumCols / 2.0f) * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

                if(x % 2 == 0) {
                    std::dynamic_pointer_cast<Pearl::OpenGLShader>(solidShader)->UploadUniformVec4("uColor", mColorA);
                } else {
                    std::dynamic_pointer_cast<Pearl::OpenGLShader>(solidShader)->UploadUniformVec4("uColor", mColorB);
                }

                Pearl::Renderer::Submit(solidShader, mSquareVA, transform);
            }
        }

        mTexture->Bind();
        Pearl::Renderer::Submit(textureShader, mSquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        mChernoLogoTexture->Bind();
        Pearl::Renderer::Submit(textureShader, mSquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        Pearl::Renderer::EndScene();
    }

    void OnEvent(Pearl::Event &event) override {
        mCameraController.OnEvent(event);
    }


    void OnImGuiRender() override {
        ImGui::Begin("Material Editor");

        ImGui::ColorEdit4("Color A", glm::value_ptr(mColorA));
        ImGui::ColorEdit4("Color B", glm::value_ptr(mColorB));

        ImGui::End();
    }

private:
    Pearl::ShaderLibrary mShaderLibrary;

    Pearl::Ref<Pearl::VertexArray> mSquareVA;

    Pearl::OrthographicCameraController mCameraController;

    Pearl::Ref<Pearl::Texture2D> mTexture;
    Pearl::Ref<Pearl::Texture2D> mChernoLogoTexture;


    glm::vec3 mSquarePosition;
    float mSquareMoveSpeed = 1.0f;

    int mNumCols = 20, mNumRows = 20;
    glm::vec4 mColorA = {0.8f, 0.2f, 0.3f, 1.0f};
    glm::vec4 mColorB = {0.2f, 0.3f, 0.8f, 1.0f};
};

class Sandbox : public Pearl::Application{
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
    }
    ~Sandbox() {

    }
};

Pearl::Application* Pearl::CreateApplication(){
    return new Sandbox();
}
