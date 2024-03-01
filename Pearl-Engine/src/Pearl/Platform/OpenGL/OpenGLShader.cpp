//
// Created by Andrew Graser on 2/25/2024.
//

#include "OpenGLShader.h"
#include "Pearl/Core/Core.h"
#include "Pearl/Core/Log.h"
#include "glm/gtc/type_ptr.hpp"


#include <Glad/glad.h>
#include <vector>
#include <array>
#include <fstream>
#include <filesystem>

namespace Pearl {

    static GLenum ShaderTypeFromString(const std::string& type){
        if(type == "vertex")            return GL_VERTEX_SHADER;
        if(type == "fragment")          return GL_FRAGMENT_SHADER;
        if(type == "pixel")             return GL_FRAGMENT_SHADER;

        PRL_CORE_ASSERT(false, "Unknown shader type");
        return 0;
    }

    OpenGLShader::OpenGLShader(const std::string &filePath) {
        auto shaderSrc = ReadFile(filePath);
        auto shaderSources = PreProcess(shaderSrc);
        Compile(shaderSources);

        std::filesystem::path path = filePath;
        mName = path.stem().string();
    }

    OpenGLShader::OpenGLShader(const std::string& name, const std::string &vertexSrc, const std::string &fragmentSrc)
        : mName(name)
    {
        std::unordered_map<GLenum, std::string> shaderSources;
        shaderSources[GL_VERTEX_SHADER] = vertexSrc;
        shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;

        Compile(shaderSources);
    }

    OpenGLShader::~OpenGLShader() {
        glDeleteProgram(mRendererID);
    }

    std::string OpenGLShader::ReadFile(const std::string &filePath) {
        std::string result;
        std::ifstream in(filePath, std::ios::in | std::ios::binary);

        if(in) {
            in.seekg(0, std::ios::end);
            result.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&result[0], result.size());

        }else {
            PRL_CORE_ERROR("Could not open in: {0}", filePath);
        }

        return result;
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string &source) {
        std::unordered_map<GLenum, std::string> shaderSources;


        const char* typeToken = "#type";
        size_t typeTokenLength   = strlen(typeToken);
        size_t pos = source.find(typeToken, 0);
        while(pos != std::string::npos){
            size_t eol = source.find_first_of("\r\n", pos);
            PRL_CORE_ASSERT(eol != std::string::npos, "Syntax Error");
            size_t begin = pos + typeTokenLength + 1;
            std::string type = source.substr(begin, eol - begin);
            PRL_CORE_ASSERT(type == "vertex" || type == "fragment" || type == "pixel", "Unknown shader type");

            size_t nextLinePos = source.find_first_not_of("\r\n", eol);
            pos = source.find(typeToken, nextLinePos);
            shaderSources[ShaderTypeFromString(type)] =
                    source.substr(nextLinePos,
                                  pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
        }

        return shaderSources;
    }

    void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string> &shaderSources) {
        GLuint program = glCreateProgram();

        PRL_CORE_ASSERT(shaderSources.size() <= 2, "No more than 2 shaders are supported");

        std::array<GLenum, 2> glShaderIDs;
        int glShaderIDIndex = 0;

        for(auto& kv : shaderSources){
            GLenum  shaderType = kv.first;
            const std::string& source = kv.second;

            GLuint shader = glCreateShader(shaderType);

            const GLchar *sourceCStr = source.c_str();
            glShaderSource(shader, 1, &sourceCStr, 0);

            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE) {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                glDeleteShader(shader);

                PRL_CORE_ASSERT(false, "Shader compilation failure!");
                PRL_CORE_ERROR("{0}", infoLog.data());

                break;
            }

            glAttachShader(program, shader);
            glShaderIDs[glShaderIDIndex++] = shader;
        }

        glLinkProgram(program);

        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int *) &isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(program);

            for(auto id : glShaderIDs){
                glDeleteShader(id);
            }

            PRL_CORE_ERROR("{0}", infoLog.data());
            PRL_CORE_ASSERT(false, "Shader link failure!");

            return;
        }

        for(auto id : glShaderIDs){
            glDetachShader(program, id);
        }

        mRendererID = program;
    }

    void OpenGLShader::Bind() const {
        glUseProgram(mRendererID);
    }

    void OpenGLShader::Unbind() const {
        glUseProgram(0);
    }

    int OpenGLShader::GetLocation(const std::string &name) {
        return glGetUniformLocation(mRendererID, name.c_str());
    }

    void OpenGLShader::UploadUniformFloat(const std::string &name, const float &v) {
        glUniform1i(GetLocation(name), v);
    }

    void OpenGLShader::UploadUniformInt(const std::string &name, const int &v) {
        glUniform1f(GetLocation(name), v);
    }

    void OpenGLShader::UploadUniformVec2(const std::string &name, const glm::vec2 &v) {
        glUniform2f(GetLocation(name), v.x, v.y);
    }

    void OpenGLShader::UploadUniformVec3(const std::string &name, const glm::vec3 &v) {
        glUniform3f(GetLocation(name), v.x, v.y, v.z);
    }

    void OpenGLShader::UploadUniformVec4(const std::string &name, const glm::vec4 &v) {
        glUniform4f(GetLocation(name), v.x, v.y, v.z, v.w);
    }

    void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4 &v) {
        glUniformMatrix4fv(GetLocation(name), 1, false, glm::value_ptr(v));
    }

    void OpenGLShader::UploadUniformMat3(const std::string &name, const glm::mat3 &v) {
        glUniformMatrix3fv(GetLocation(name), 1, false, glm::value_ptr(v));
    }
}