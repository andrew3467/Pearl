//
// Created by Andrew Graser on 2/25/2024.
//

#ifndef PEARL_OPENGLSHADER_H
#define PEARL_OPENGLSHADER_H

#include "Pearl/Renderer/Shader.h"

#include <stdint.h>

#include <glm/glm.hpp>


namespace Pearl {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc);
        virtual ~OpenGLShader() override;

        virtual void Bind() const override;
        virtual void Unbind() const override;

        void UploadUniformMat4(const std::string& name, const glm::mat4& v);
        void UploadUniformVec4(const std::string& name, const glm::vec4& v);

    private:
        int GetLocation(const std::string& name);

    private:
        uint32_t mRendererID;
    };
}


#endif //PEARL_OPENGLSHADER_H
