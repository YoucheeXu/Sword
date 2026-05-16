#include "OpenGLVertexArray.h"

#include <cstdint>
#include <glad/glad.h>

namespace Sword {

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
    switch (type) {
        case Sword::ShaderDataType::Float:
            return GL_FLOAT;
        case Sword::ShaderDataType::Float2:
            return GL_FLOAT;
        case Sword::ShaderDataType::Float3:
            return GL_FLOAT;
        case Sword::ShaderDataType::Float4:
            return GL_FLOAT;
        case Sword::ShaderDataType::Mat3:
            return GL_FLOAT;
        case Sword::ShaderDataType::Mat4:
            return GL_FLOAT;
        case Sword::ShaderDataType::Int:
            return GL_INT;
        case Sword::ShaderDataType::Int2:
            return GL_INT;
        case Sword::ShaderDataType::Int3:
            return GL_INT;
        case Sword::ShaderDataType::Int4:
            return GL_INT;
        case Sword::ShaderDataType::Bool:
            return GL_BOOL;
        case Sword::ShaderDataType::None:
            return GL_NONE;
    }

    SW_CORE_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
}

OpenGLVertexArray::OpenGLVertexArray() {
    glCreateVertexArrays(1, &m_RendererID);
}

OpenGLVertexArray::~OpenGLVertexArray() {
    glDeleteVertexArrays(1, &m_RendererID);
}

void OpenGLVertexArray::Bind() const {
    glBindVertexArray(m_RendererID);
}

void OpenGLVertexArray::Unbind() const {
    glBindVertexArray(0);
}

void OpenGLVertexArray::AddVertexBuffer(Ref<VertexBuffer> const& vertexBuffer) {
    SW_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

    glBindVertexArray(m_RendererID);
    vertexBuffer->Bind();

    uint32_t    index  = 0;
    auto const& layout = vertexBuffer->GetLayout();
    for (auto const& element : layout) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index,
                              element.GetComponentCount(),
                              ShaderDataTypeToOpenGLBaseType(element.Type),
                              element.Normalized ? GL_TRUE : GL_FALSE,
                              layout.GetStride(),
                              (void const*)element.Offset);
        index++;
    }

    m_VertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::SetIndexBuffer(Ref<IndexBuffer> const& indexBuffer) {
    glBindVertexArray(m_RendererID);
    indexBuffer->Bind();

    m_IndexBuffer = indexBuffer;
}

}  // namespace Sword