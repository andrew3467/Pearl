//
// Created by Andrew Graser on 2/19/2024.
//

#include "Shader.h"
#include "Pearl/Core/Core.h"
#include "Pearl/Core/Log.h"
#include "Renderer.h"
#include "Pearl/Platform/OpenGL/OpenGLShader.h"

#include <Glad/glad.h>
#include <vector>

#include <glm/gtc/type_ptr.hpp>

namespace Pearl {

    Ref<Shader> Shader::Create(const std::string &filePath) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:             /*PRL_CORE_ASSERT(false, "Renderer API::None is currently not supported!"); */return nullptr;
            case RendererAPI::API::OpenGL:           return std::make_shared<OpenGLShader>(filePath);
        }

        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string& name, const std::string &vertexSrc, const std::string &fragmentSrc) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:             /*PRL_CORE_ASSERT(false, "Renderer API::None is currently not supported!"); */return nullptr;
            case RendererAPI::API::OpenGL:           return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }

        return nullptr;
    }

    void ShaderLibrary::Add(const Ref<Shader> &shader, const std::string &name) {
        PRL_CORE_ASSERT(mShaders.find(name) == mShaders.end(), "Shader already exists!");
        mShaders[name] = shader;
    }

    void ShaderLibrary::Add(const Ref<Shader> &shader) {
        auto& name = shader->GetName();
        Add(shader, name);
    }

    Ref<Shader> ShaderLibrary::Load(const std::string &filepath) {
        auto shader = Shader::Create(filepath);
        Add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string &filepath, const std::string &name) {
        auto shader = Shader::Create(filepath);
        Add(shader, name);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Get(const std::string &name) {
        PRL_CORE_ASSERT(mShaders.find(name) != mShaders.end(), "Shader not found!");
        return mShaders[name];
    }
}