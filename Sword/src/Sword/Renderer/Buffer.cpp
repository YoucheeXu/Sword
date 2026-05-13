#include "Buffer.h"

#include "Sword/Core/Core.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Sword {
VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
    switch (RendererAPI::GetAPI()) {
        case Sword::RendererAPI::API::None:
            SW_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
    }

    SW_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count) {
    switch (RendererAPI::GetAPI()) {
        case Sword::RendererAPI::API::None:
            SW_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, count);
    }

    SW_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}
}  // namespace Sword