//
// Created by Andrew Graser on 2/19/2024.
//

#ifndef PEARL_SHADER_H
#define PEARL_SHADER_H


#include <string>


namespace Pearl {
    class Shader {
    public:
        virtual ~Shader() = default;


        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;


        static Shader* Create(const std::string &vertexSrc, const std::string &fragmentSrc);
    };
}


#endif //PEARL_SHADER_H
