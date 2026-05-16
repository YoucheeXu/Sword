#ifndef OPENGLVERTEXARRAY_H
#define OPENGLVERTEXARRAY_H

#pragma once

#include "Sword/Core/Base.h"
#include "Sword/Renderer/VertexArray.h"

namespace Sword {

class OpenGLVertexArray : public VertexArray {
public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void AddVertexBuffer(Ref<VertexBuffer> const& vertexBuffer) override;
    virtual void SetIndexBuffer(Ref<IndexBuffer> const& indexBuffer) override;

    virtual std::vector<Ref<VertexBuffer>> const& GetVertexBuffers() const override {
        return m_VertexBuffers;
    }
    virtual Ref<IndexBuffer> const& GetIndexBuffer() const override {
        return m_IndexBuffer;
    }

private:
    uint32_t                       m_RendererID;
    std::vector<Ref<VertexBuffer>> m_VertexBuffers;
    Ref<IndexBuffer>               m_IndexBuffer;

private:
};

}  // namespace Sword

#endif