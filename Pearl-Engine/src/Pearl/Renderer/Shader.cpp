//
// Created by Andrew Graser on 2/19/2024.
//

#include "Shader.h"
#include "Pearl/Core.h"
#include "Pearl/Log.h"
#include "Renderer.h"
#include "Pearl/Platform/OpenGL/OpenGLShader.h"

#include <Glad/glad.h>
#include <vector>

#include <glm/gtc/type_ptr.hpp>

namespace Pearl {

    Shader *Shader::Create(const std::string &vertexSrc, const std::string &fragmentSrc) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:             /*PRL_CORE_ASSERT(false, "Renderer API::None is currently not supported!"); */return nullptr;
            case RendererAPI::API::OpenGL:           return new OpenGLShader(vertexSrc, fragmentSrc);
        }

        return nullptr;
    }
}