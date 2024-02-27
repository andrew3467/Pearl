//
// Created by Andrew Graser on 2/26/2024.
//

#ifndef PEARL_OPENGLTEXTURE_H
#define PEARL_OPENGLTEXTURE_H

#include "Pearl/Renderer/Texture.h"


namespace Pearl {
    class OpenGLTexture2D : public Texture2D {
    public:
        OpenGLTexture2D(const std::string& path);
        ~OpenGLTexture2D() override;

        virtual uint32_t GetWidth() const override {return mWidth;};
        virtual uint32_t GetHeight() const override {return mHeight;};

        virtual void Bind() const override;

    private:
        uint32_t mWidth, mHeight;
        std::string mPath;
    };
}


#endif //PEARL_OPENGLTEXTURE_H
