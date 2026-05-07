#ifndef OPENGLVERTEXARRAY_H
#define OPENGLVERTEXARRAY_H

#pragma once

#include "Sword/Renderer/VertexArray.h"

#include <memory.h>

namespace Sword {

class OpenGLVertexArray : public VertexArray {
public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer> const& vertexBuffer) override;
    virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer> const& indexBuffer) override;

    virtual std::vector<std::shared_ptr<VertexBuffer>> const& GetVertexBuffers() const override {
        return m_VertexBuffers;
    }
    virtual std::shared_ptr<IndexBuffer> const& GetIndexBuffer() const override {
        return m_IndexBuffer;
    }

private:
    uint32_t                                   m_RendererID;
    std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
    std::shared_ptr<IndexBuffer>               m_IndexBuffer;

private:
};

}  // namespace Sword

#endif