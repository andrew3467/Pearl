//
// Created by Andrew Graser on 2/23/2024.
//

#ifndef PEARL_OPENGLVERTEXARRAY_H
#define PEARL_OPENGLVERTEXARRAY_H


#include "Pearl/Renderer/VertexArray.h"

namespace Pearl {
    class OpenGLVertexArray : public VertexArray {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray() override;

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

        virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override {return mVertexBuffers;}
        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override {return mIndexBuffer;}

        virtual void Bind() const override;
        virtual void Unbind() const override;

    private:
        std::vector<std::shared_ptr<VertexBuffer>> mVertexBuffers;
        std::shared_ptr<IndexBuffer> mIndexBuffer;
        unsigned int mRendererID;
    };
}


#endif //PEARL_OPENGLVERTEXARRAY_H
