//
// Created by Andrew Graser on 2/5/2024.
//

#include <Pearl.h>

#include <imgui.h>


class ExampleLayer : public Pearl::Layer{
public:
    ExampleLayer()
        : Layer("Example"), mCamera(-1.6f, 1.6f, -0.9f, 0.9f), mCameraPosition(0.0f) {
        mVertexArray.reset(Pearl::VertexArray::Create());

        float vertices[3 * 7] = {
                -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        };

        uint32_t indices[3] = {
                0, 1, 2,
        };

        std::shared_ptr<Pearl::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(Pearl::VertexBuffer::Create(vertices, sizeof(vertices)));

        Pearl::BufferLayout layout = {
                {Pearl::ShaderDataType::Float3, "aPosition"},
                {Pearl::ShaderDataType::Float4, "aColor"},
        };

        vertexBuffer->SetLayout(layout);
        mVertexArray->AddVertexBuffer(vertexBuffer);


        std::shared_ptr<Pearl::IndexBuffer> indexBuffer;
        indexBuffer.reset(Pearl::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        mVertexArray->SetIndexBuffer(indexBuffer);

        mSquareVA.reset(Pearl::VertexArray::Create());

        float squareVertices[4 * 3] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.5f, 0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f,
        };

        uint32_t squareIndices[6] = {
                0, 1, 2,
                2, 3, 0
        };

        std::shared_ptr<Pearl::VertexBuffer> squareVB;
        squareVB.reset(Pearl::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        squareVB->SetLayout({
                                    {Pearl::ShaderDataType::Float3, "aPosition"},
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

            out vec3 vPosition;
            out vec4 vColor;

            void main() {
                vColor = aColor;
                vPosition = aPosition;

                gl_Position = uViewProjection * vec4(aPosition, 1.0);
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


        mShader.reset(new Pearl::Shader(vertexSrc, fragmentSrc));

        std::string blueShaderVertexSrc = R"(
            #version 460 core

            layout(location = 0) in vec3 aPosition;

            uniform mat4 uViewProjection;

            out vec3 vPosition;

            void main() {
                vPosition = aPosition;

                gl_Position = uViewProjection * vec4(aPosition, 1.0);
            }
        )";

        std::string blueShaderFragmentSrc = R"(
            #version 460 core

            layout(location = 0) out vec4 color;

            in vec3 vPosition;

            void main() {
                color = vec4(0.2, 0.3, 0.8, 1.0);
            }
        )";


        mBlueShader.reset(new Pearl::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
    }

    void OnUpdate() override {
        if(Pearl::Input::IsKeyPressed(PRL_KEY_A)){
            mCameraPosition.x -= mCameraMoveSpeed;
        }

        if(Pearl::Input::IsKeyPressed(PRL_KEY_D)){
            mCameraPosition.x += mCameraMoveSpeed;
        }

        if(Pearl::Input::IsKeyPressed(PRL_KEY_S)){
            mCameraPosition.y += mCameraMoveSpeed;
        }

        if(Pearl::Input::IsKeyPressed(PRL_KEY_W)){
            mCameraPosition.y -= mCameraMoveSpeed;
        }

        if(Pearl::Input::IsKeyPressed(PRL_KEY_LEFT)){
            mCameraRotation += mCameraRotationSpeed;
        }

        if(Pearl::Input::IsKeyPressed(PRL_KEY_RIGHT)){
            mCameraRotation -= mCameraRotationSpeed;
        }



        Pearl::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Pearl::RenderCommand::Clear();

        mCamera.SetPosition(mCameraPosition);
        mCamera.SetRotation(mCameraRotation);

        Pearl::Renderer::BeginScene(mCamera);

        Pearl::Renderer::Submit(mBlueShader, mSquareVA);
        Pearl::Renderer::Submit(mShader, mVertexArray);

        Pearl::Renderer::EndScene();
    }

    void OnEvent(Pearl::Event &event) override {

    }


    void OnImGuiRender() override {

    }

private:
    std::shared_ptr<Pearl::Shader> mBlueShader;
    std::shared_ptr<Pearl::Shader> mShader;

    std::shared_ptr<Pearl::VertexArray> mVertexArray;
    std::shared_ptr<Pearl::VertexArray> mSquareVA;

    Pearl::OrthographicCamera mCamera;

    glm::vec3 mCameraPosition;
    float mCameraMoveSpeed = 0.1f;

    float mCameraRotation = 0.0f;
    float mCameraRotationSpeed = 2.0f;
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
