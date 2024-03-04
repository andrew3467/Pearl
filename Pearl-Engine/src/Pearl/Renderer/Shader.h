//
// Created by Andrew Graser on 2/19/2024.
//

#ifndef PEARL_SHADER_H
#define PEARL_SHADER_H


#include <string>
#include <unordered_map>

#include <Pearl/Core/Core.h>
#include "glm/glm.hpp"


namespace Pearl {
    class Shader {
    public:
        virtual ~Shader() = default;


        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;


        virtual const std::string& GetName() const = 0;

        virtual void SetInt(const std::string& name, const int& v) = 0;

        virtual void SetFloat(const std::string& name, const float& v) = 0;
        virtual void SetFloat2(const std::string& name, const glm::vec2& v) = 0;
        virtual void SetFloat3(const std::string& name, const glm::vec3& v) = 0;
        virtual void SetFloat4(const std::string& name, const glm::vec4& v) = 0;

        virtual void SetMat4(const std::string& name, const glm::mat4& v) = 0;
        virtual void SetMat3(const std::string& name, const glm::mat3& v) = 0;

        static Ref<Shader> Create(const std::string &filePath);
        static Ref<Shader> Create(const std::string& name, const std::string &vertexSrc, const std::string &fragmentSrc);
    };

    class ShaderLibrary {
    public:
        void Add(const Ref<Shader>& shader);
        void Add(const Ref<Shader>& shader, const std::string& name);
        Ref<Shader> Load(const std::string& filepath);
        Ref<Shader> Load(const std::string& filepath, const std::string& name);

        Ref<Shader> Get(const std::string& name);

    private:
        std::unordered_map<std::string, Ref<Shader>> mShaders;
    };
}


#endif //PEARL_SHADER_H
