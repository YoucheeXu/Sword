#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <memory>
#pragma once

#include "Sword/Renderer/Buffer.h"

#include <memory.h>

namespace Sword {

class VertexArray {
public:
    virtual ~VertexArray() = default;

    virtual void Bind() const   = 0;
    virtual void Unbind() const = 0;

    virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer> const& vertexBuffer) = 0;
    virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer> const& indexBuffer)    = 0;

    virtual std::vector<std::shared_ptr<VertexBuffer>> const& GetVertexBuffers() const = 0;
    virtual std::shared_ptr<IndexBuffer> const&               GetIndexBuffer() const   = 0;

    static VertexArray* Create();

private:
};

}  // namespace Sword

#endif