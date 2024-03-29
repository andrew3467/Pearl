//
// Created by Andrew Graser on 2/25/2024.
//

#ifndef PEARL_OPENGLSHADER_H
#define PEARL_OPENGLSHADER_H

#include "Pearl/Renderer/Shader.h"

#include <stdint.h>

#include <glm/glm.hpp>
#include <unordered_map>


typedef unsigned int GLenum;

namespace Pearl {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string &filePath);
        OpenGLShader(const std::string& name, const std::string &vertexSrc, const std::string &fragmentSrc);
        virtual ~OpenGLShader() override;

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual const std::string& GetName() const override {return mName;};

        void SetFloat(const std::string& name, const float& v) override;
        void SetInt(const std::string& name, const int& v) override;

        void SetFloat2(const std::string& name, const glm::vec2& v) override;
        void SetFloat3(const std::string& name, const glm::vec3& v) override;
        void SetFloat4(const std::string& name, const glm::vec4& v) override;

        void SetMat4(const std::string& name, const glm::mat4& v) override;
        void SetMat3(const std::string& name, const glm::mat3& v) override;

    private:
        int GetLocation(const std::string& name);

        std::string ReadFile(const std::string& filePath);
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
        void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);


    private:
        uint32_t mRendererID;
        std::string mName;
    };
}


#endif //PEARL_OPENGLSHADER_H
