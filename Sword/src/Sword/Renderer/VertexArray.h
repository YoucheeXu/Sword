#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#pragma once

#include "Sword/Core/Base.h"
#include "Sword/Renderer/Buffer.h"

namespace Sword {

class VertexArray {
public:
    virtual ~VertexArray() = default;

    virtual void Bind() const   = 0;
    virtual void Unbind() const = 0;

    virtual void AddVertexBuffer(Ref<VertexBuffer> const& vertexBuffer) = 0;
    virtual void SetIndexBuffer(Ref<IndexBuffer> const& indexBuffer)    = 0;

    virtual std::vector<Ref<VertexBuffer>> const& GetVertexBuffers() const = 0;
    virtual Ref<IndexBuffer> const&               GetIndexBuffer() const   = 0;

    static Ref<VertexArray> Create();

private:
};

}  // namespace Sword

#endif