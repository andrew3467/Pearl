//
// Created by Andrew Graser on 2/26/2024.
//

#ifndef PEARL_TEXTURE_H
#define PEARL_TEXTURE_H


#include <cstdint>
#include <string>
#include "Pearl/Core.h"

namespace Pearl {
    class Texture {
    public:
        virtual ~Texture() = default;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void Bind() const = 0;
    };


    class Texture2D : public Texture {
    public:
        static Ref<Texture2D> Create(const std::string& path);
    };
}


#endif //PEARL_TEXTURE_H
