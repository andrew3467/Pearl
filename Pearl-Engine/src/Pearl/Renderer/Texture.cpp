//
// Created by Andrew Graser on 2/26/2024.
//

#include "Texture.h"
#include "RendererAPI.h"
#include "Renderer.h"
#include "Pearl/Platform/OpenGL/OpenGLTexture.h"

namespace Pearl {

    Ref<Texture2D> Texture2D::Create(const std::string &path) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:             /*PRL_CORE_ASSERT(false, "Renderer API::None is currently not supported!"); */return nullptr;
            case RendererAPI::API::OpenGL:           return std::make_shared<OpenGLTexture2D>(path);
        }

        return nullptr;
    }
}