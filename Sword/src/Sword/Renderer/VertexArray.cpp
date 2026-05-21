#include "VertexArray.h"

#include <memory>

#include "Sword/Core/Assert.h"
#include "Sword/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Sword {

Ref<VertexArray> VertexArray::Create() {
    switch (RendererAPI::GetAPI()) {
        case RendererAPI::API::None:
            SW_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexArray>();
    }

    SW_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

}  // namespace Sword