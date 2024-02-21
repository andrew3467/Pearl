//
// Created by Andrew Graser on 2/5/2024.
//

#include "Application.h"
#include "Log.h"

#include "Pearl/Input.h"


#include <Glad/glad.h>

namespace Pearl {
#define BIND_EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)

    Application* Application::sInstance = nullptr;

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type){
        switch (type) {
            case ShaderDataType::Float:             return GL_FLOAT;
            case ShaderDataType::Float2:            return GL_FLOAT;
            case ShaderDataType::Float3:            return GL_FLOAT;
            case ShaderDataType::Float4:            return GL_FLOAT;

            case ShaderDataType::Int:               return GL_INT;
            case ShaderDataType::Int2:              return GL_INT;
            case ShaderDataType::Int3:              return GL_INT;
            case ShaderDataType::Int4:              return GL_INT;

            case ShaderDataType::Mat3:              return GL_FLOAT;
            case ShaderDataType::Mat4:              return GL_FLOAT;

            case ShaderDataType::Bool:              return GL_BOOL;
        }

        PRL_CORE_ASSERT(false, "Unknown shader data type!");
        return 0;
    }

    Application::Application() {
        Pearl::Log::Init();

        PRL_ASSERT(sInstance == nullptr, "Only 1 Application instance may exist")
        sInstance = this;

        mWindow = std::unique_ptr<Window>(Window::Create());
        mWindow->SetEventCallback(BIND_EVENT_FUNC(Application::OnEvent));

        mImGuiLayer = new ImGuiLayer();
        PushOverlay(mImGuiLayer);

        glGenVertexArrays(1, &mVertexArray);
        glBindVertexArray(mVertexArray);

        float vertices[3 * 7] = {
                -0.5f, -0.5f, 0.0f,                  1.0f, 0.0f, 1.0f, 1.0f,
                0.5f, -0.5f, 0.0f,                  0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.5f, 0.0f,                 1.0f, 1.0f, 0.0f, 1.0f,
        };

        uint32_t indices[3] = {
                0, 2, 1
        };

        mVertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        mVertexBuffer->Bind();

        {
            BufferLayout layout = {
                    {ShaderDataType::Float3, "aPosition"},
                    {ShaderDataType::Float4, "aColor"},
            };

            mVertexBuffer->SetLayout(layout);
        }

        uint32_t index = 0;
        const auto& layout = mVertexBuffer->GetLayout();
        for(const auto& element : layout){
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                                  element.GetElementCount(),
                                  ShaderDataTypeToOpenGLBaseType(element.Type),
                                  element.Normalized ? GL_TRUE : GL_FALSE,
                                  layout.GetStride(),
                                  (const void*)element.Offset);
            index++;
        }


        mIndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        mIndexBuffer->Bind();


        std::string vertexSrc = R"(
            #version 460 core

            layout(location = 0) in vec3 aPosition;
            layout(location = 1) in vec4 aColor;

            out vec3 vPosition;
            out vec4 vColor;

            void main() {
                vColor = aColor;
                vPosition = aPosition;

                gl_Position = vec4(aPosition, 1.0);
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


        mShader.reset(new Shader(vertexSrc, fragmentSrc));
    }

    Application::~Application() {

    }


    void Application::Run() {
        while(mRunning){
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);


            mShader->Bind();
            glBindVertexArray(mVertexArray);
            glDrawElements(GL_TRIANGLES, mIndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);


            for(Layer* layer : mLayerStack){
                layer->OnUpdate();
            }

            mImGuiLayer->Begin();
            for(Layer* layer : mLayerStack){
                layer->OnImGuiRender();
            }
            mImGuiLayer->End();

            mWindow->OnUpdate();
        }
    }

    void Application::OnEvent(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Application::OnWindowClosed));

        for(auto it = mLayerStack.end(); it != mLayerStack.begin(); ){
            (*--it)->OnEvent(e);
            if(e.Handled){
                break;
            }
        }
    }

    bool Application::OnWindowClosed(WindowCloseEvent &e) {
        mRunning = false;

        return true;
    }

    void Application::PushLayer(Layer *layer) {
        mLayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *overlay) {
        mLayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }
}