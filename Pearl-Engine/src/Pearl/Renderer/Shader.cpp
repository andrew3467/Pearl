//
// Created by Andrew Graser on 2/19/2024.
//

#include "Shader.h"
#include "Pearl/Core.h"
#include "Pearl/Log.h"

#include <Glad/glad.h>
#include <vector>

namespace Pearl {

    Shader::Shader(const std::string &vertexSrc, const std::string &fragmentSrc) {
// Create an empty vertex shader handle
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

// Send the vertex shader source code to GL
// Note that std::string's .c_str is NULL character terminated.
        const GLchar *source = (const GLchar *) vertexSrc.c_str();
        glShaderSource(vertexShader, 1, &source, 0);

// Compile the vertex shader
        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(vertexShader);

            PRL_CORE_ASSERT(false, "Vertex shader compilation failure!");
            PRL_CORE_ERROR("{0}", infoLog.data());

            // Use the infoLog as you see fit.

            // In this simple mRendererID, we'll just leave
            return;
        }

// Create an empty fragment shader handle
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

// Send the fragment shader source code to GL
// Note that std::string's .c_str is NULL character terminated.
        source = (const GLchar *) fragmentSrc.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);

// Compile the fragment shader
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(fragmentShader);
            // Either of them. Don't leak shaders.
            glDeleteShader(vertexShader);

            PRL_CORE_ASSERT(false, "Fragment shader compilation failure!");
            PRL_CORE_ERROR("{0}", infoLog.data());

            // Use the infoLog as you see fit.

            // In this simple mRendererID, we'll just leave
            return;
        }

// Vertex and fragment shaders are successfully compiled.
// Now time to link them together into a mRendererID.
// Get a mRendererID object.
        mRendererID = glCreateProgram();

// Attach our shaders to our mRendererID
        glAttachShader(mRendererID, vertexShader);
        glAttachShader(mRendererID, fragmentShader);

// Link our mRendererID
        glLinkProgram(mRendererID);

// Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(mRendererID, GL_LINK_STATUS, (int *) &isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(mRendererID, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(mRendererID, maxLength, &maxLength, &infoLog[0]);

            // We don't need the mRendererID anymore.
            glDeleteProgram(mRendererID);
            // Don't leak shaders either.
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            PRL_CORE_ERROR("{0}", infoLog.data());
            PRL_CORE_ASSERT(false, "Shader link failure!");

            // Use the infoLog as you see fit.

            // In this simple mRendererID, we'll just leave
            return;
        }

// Always detach shaders after a successful link.
        glDetachShader(mRendererID, vertexShader);
        glDetachShader(mRendererID, fragmentShader);
    }

    Shader::~Shader() {
        glDeleteProgram(mRendererID);
    }

    void Shader::Bind() const {
        glUseProgram(mRendererID);
    }

    void Shader::Unbind() const {
        glUseProgram(0);
    }
}