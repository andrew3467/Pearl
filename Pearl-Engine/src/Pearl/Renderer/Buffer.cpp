//
// Created by Andrew Graser on 2/20/2024.
//

#include "Buffer.h"

#include "Renderer.h"
#include "Pearl/Core/Core.h"
#include "Pearl/Platform/OpenGL/OpenGLBuffer.h"

namespace Pearl {

    VertexBuffer *VertexBuffer::Create(float *vertices, uint32_t size) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:             /*PRL_CORE_ASSERT(false, "Renderer API::None is currently not supported!"); */return nullptr;
            case RendererAPI::API::OpenGL:           return new OpenGLVertexBuffer(vertices, size);
        }

        return nullptr;
    }

    IndexBuffer *IndexBuffer::Create(uint32_t *indices, uint32_t size) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:             /*PRL_CORE_ASSERT(false, "Renderer API::None is currently not supported!"); */return nullptr;
            case RendererAPI::API::OpenGL:           return new OpenGLIndexBuffer(indices, size);
        }

        return nullptr;
    }
}