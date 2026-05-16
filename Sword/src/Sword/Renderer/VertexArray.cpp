#include "VertexArray.h"

#include "Sword/Core/Assert.h"
#include "Sword/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Sword {

VertexArray* VertexArray::Create() {
    switch (RendererAPI::GetAPI()) {
        case RendererAPI::API::None:
            SW_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
    }

    SW_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

}  // namespace Sword