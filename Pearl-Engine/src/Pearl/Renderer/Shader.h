//
// Created by Andrew Graser on 2/19/2024.
//

#ifndef PEARL_SHADER_H
#define PEARL_SHADER_H


#include <string>
#include <cstdint>

namespace Pearl {
    class Shader {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void Bind() const;
        void Unbind() const;

    private:
        uint32_t mRendererID;
    };
}


#endif //PEARL_SHADER_H
