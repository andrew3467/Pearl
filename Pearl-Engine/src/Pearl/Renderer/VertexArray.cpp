//
// Created by Andrew Graser on 2/23/2024.
//

#include "VertexArray.h"
#include "Renderer.h"
#include "Pearl/Platform/OpenGL/OpenGLVertexArray.h"


namespace Pearl {

    Ref<VertexArray> VertexArray::Create() {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:             /*PRL_CORE_ASSERT(false, "Renderer API::None is currently not supported!"); */return nullptr;
            case RendererAPI::API::OpenGL:           return std::make_shared<OpenGLVertexArray>();
        }

        return nullptr;
    }
}