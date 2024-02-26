//
// Created by Andrew Graser on 2/23/2024.
//

#ifndef PEARL_VERTEXARRAY_H
#define PEARL_VERTEXARRAY_H

#include "Pearl/Renderer/Buffer.h"

namespace Pearl {
    class VertexArray {
        public:
            virtual ~VertexArray() = default;

            virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
            virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

            virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
            virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

            static VertexArray* Create();

            virtual void Bind() const = 0;
            virtual void Unbind() const = 0;
        };
}


#endif //PEARL_VERTEXARRAY_H
