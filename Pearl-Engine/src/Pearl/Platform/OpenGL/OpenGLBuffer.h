//
// Created by Andrew Graser on 2/20/2024.
//

#ifndef PEARL_OPENGLBUFFER_H
#define PEARL_OPENGLBUFFER_H

#include "Pearl/Renderer/Buffer.h"


namespace Pearl {
    class OpenGLVertexBuffer : public VertexBuffer{
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        ~OpenGLVertexBuffer() override;

        virtual void SetLayout(const BufferLayout& layout) override {mLayout = layout;}
        virtual const BufferLayout& GetLayout() const { return mLayout;}

        virtual void Bind() const override;
        virtual void Unbind() const override;

    private:
        uint32_t mRendererID;
        BufferLayout mLayout;
    };

    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer(uint32_t *indices, uint32_t count);
        ~OpenGLIndexBuffer() override;

        virtual uint32_t GetCount() const override;

        virtual void Bind() const override;
        virtual void Unbind() const override;



    private:
        uint32_t mRendererID;
        uint32_t mCount;
    };
}


#endif //PEARL_OPENGLBUFFER_H
