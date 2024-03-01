//
// Created by Andrew Graser on 2/19/2024.
//

#ifndef PEARL_SHADER_H
#define PEARL_SHADER_H


#include <string>
#include <unordered_map>

#include <Pearl/Core/Core.h>


namespace Pearl {
    class Shader {
    public:
        virtual ~Shader() = default;


        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;


        virtual const std::string& GetName() const = 0;

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
