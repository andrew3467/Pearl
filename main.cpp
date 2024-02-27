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
        : Layer("Example"), mCamera(-1.6f, 1.6f, -0.9f, 0.9f), mCameraPosition(0.0f), mSquarePosition(0.0f) {
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


        std::string vertexSrc = R"(
            #version 460 core

            layout(location = 0) in vec3 aPosition;
            layout(location = 1) in vec4 aColor;

            uniform mat4 uViewProjection;
            uniform mat4 uTransform;

            out vec3 vPosition;
            out vec4 vColor;

            void main() {
                vColor = aColor;
                vPosition = aPosition;

                gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 460 core

            layout(location = 0) out vec4 color;

            in vec3 vPosition;
            in vec4 vColor;

            void main() {
                color = vColor;
            }
        )";


        mShader.reset(Pearl::Shader::Create(vertexSrc, fragmentSrc));

        std::string solidShaderVertexSrc = R"(
            #version 460 core

            layout(location = 0) in vec3 aPosition;

            uniform mat4 uViewProjection;
            uniform mat4 uTransform;

            out vec3 vPosition;

            void main() {
                vPosition = aPosition;

                gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0);
            }
        )";

        std::string solidShaderFragmentSrc = R"(
            #version 460 core

            layout(location = 0) out vec4 color;

            in vec3 vPosition;

            uniform vec4 uColor;

            void main() {
                color = uColor;
            }
        )";


        mSolidShader.reset(Pearl::Shader::Create(solidShaderVertexSrc, solidShaderFragmentSrc));

        std::string textureShaderVertexSrc = R"(
            #version 460 core

            layout(location = 0) in vec3 aPosition;
            layout(location = 1) in vec2 aTexCoord;

            uniform mat4 uViewProjection;
            uniform mat4 uTransform;

            out vec2 vTexCoord;


            void main() {
                vTexCoord = aTexCoord;

                gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0);
            }
        )";

        std::string textureShaderFragmentSrc = R"(
            #version 460 core

            layout(location = 0) out vec4 color;

            in vec2 vTexCoord;

            void main() {
                color = vec4(vTexCoord, 0.0, 1.0);
            }
        )";


        mTextureShader.reset(Pearl::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));
    }

    void OnUpdate(Pearl::Timestep ts) override {

        if(Pearl::Input::IsKeyPressed(PRL_KEY_A)){
            mCameraPosition.x -= mCameraMoveSpeed * ts;
        }

        if(Pearl::Input::IsKeyPressed(PRL_KEY_D)){
            mCameraPosition.x += mCameraMoveSpeed * ts;
        }

        if(Pearl::Input::IsKeyPressed(PRL_KEY_S)){
            mCameraPosition.y -= mCameraMoveSpeed * ts;
        }

        if(Pearl::Input::IsKeyPressed(PRL_KEY_W)){
            mCameraPosition.y += mCameraMoveSpeed * ts;
        }

        if(Pearl::Input::IsKeyPressed(PRL_KEY_LEFT)){
            mCameraRotation += mCameraRotationSpeed * ts;
        }

        if(Pearl::Input::IsKeyPressed(PRL_KEY_RIGHT)){
            mCameraRotation -= mCameraRotationSpeed * ts;
        }

        if(Pearl::Input::IsKeyPressed(PRL_KEY_UP)){
            mSquarePosition.y += mSquareMoveSpeed * ts;
        }

        if(Pearl::Input::IsKeyPressed(PRL_KEY_DOWN)){
            mSquarePosition.y -= mSquareMoveSpeed * ts;
        }



        Pearl::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Pearl::RenderCommand::Clear();

        mCamera.SetPosition(mCameraPosition);
        mCamera.SetRotation(mCameraRotation);

        Pearl::Renderer::BeginScene(mCamera);


        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));


        std::dynamic_pointer_cast<Pearl::OpenGLShader>(mSolidShader)->Bind();
        for(int y = 0; y < mNumCols; y++){
            for (int x = 0; x < mNumRows; ++x) {
                glm::vec3 pos((x - mNumRows / 2.0f) * 0.11f, (y - mNumCols / 2.0f) * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

                if(x % 2 == 0) {
                    std::dynamic_pointer_cast<Pearl::OpenGLShader>(mSolidShader)->UploadUniformVec4("uColor", mColorA);
                } else {
                    std::dynamic_pointer_cast<Pearl::OpenGLShader>(mSolidShader)->UploadUniformVec4("uColor", mColorB);
                }

                Pearl::Renderer::Submit(mSolidShader, mSquareVA, transform);
            }
        }

        Pearl::Renderer::Submit(mTextureShader, mSquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        Pearl::Renderer::EndScene();
    }

    void OnEvent(Pearl::Event &event) override {

    }


    void OnImGuiRender() override {
        ImGui::Begin("Material Editor");

        ImGui::ColorEdit4("Color A", glm::value_ptr(mColorA));
        ImGui::ColorEdit4("Color B", glm::value_ptr(mColorB));

        ImGui::End();
    }

private:
    Pearl::Ref<Pearl::Shader> mSolidShader;
    Pearl::Ref<Pearl::Shader> mShader;
    Pearl::Ref<Pearl::Shader> mTextureShader;

    Pearl::Ref<Pearl::VertexArray> mSquareVA;

    Pearl::OrthographicCamera mCamera;

    glm::vec3 mCameraPosition;
    float mCameraMoveSpeed = 2.5f;

    float mCameraRotation = 0.0f;
    float mCameraRotationSpeed = 180.0f;

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
