//
// Created by Andrew Graser on 2/26/2024.
//

#include "OpenGLTexture.h"
#include "Pearl/Core/Core.h"
#include "Pearl/Core/Log.h"

#include <Glad/glad.h>
#include <stbimage/stb_image.h>

namespace Pearl {
    OpenGLTexture2D::OpenGLTexture2D(const std::string &path)
        : mPath(path)
    {
        int width, height, channels;
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

        PRL_CORE_ASSERT(data, "Failed to load image")

        mWidth = width;
        mHeight = height;


        GLenum internalFormat = 0, dataFormat = 0;
        if(channels == 4) {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        } else if(channels == 3) {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        PRL_CORE_ASSERT(internalFormat & dataFormat, "Texture format not supported")


        glCreateTextures(GL_TEXTURE_2D, 1, &mRendererID);
        glTextureStorage2D(mRendererID, 1, internalFormat, mWidth, mHeight);

        glTextureParameteri(mRendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(mRendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureSubImage2D(mRendererID, 0, 0, 0, mWidth, mHeight, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D() {
        glDeleteTextures(1, &mRendererID);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const {
        glBindTextureUnit(slot, mRendererID);
    }
}
