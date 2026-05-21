#include "Texture.h"

#include "Sword/Core/Assert.h"
#include "Sword/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Sword {
Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
    switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            SW_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(width, height);
    }

    SW_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

Ref<Texture2D> Texture2D::Create(std::string const& path) {
    switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            SW_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path);
    }

    SW_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

}  // namespace Sword