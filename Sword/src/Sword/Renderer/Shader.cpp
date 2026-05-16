#include "Shader.h"
#include "Sword/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Sword {
    Shader* Shader::Create(std::string const& filepath)
    {
        switch (RendererAPI::GetAPI()) {
            case RendererAPI::API::None:
                SW_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLShader(filepath);
        }

        SW_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }


Shader* Shader::Create(std::string const& vertexSrc, std::string const& fragmentSrc) {
    switch (RendererAPI::GetAPI()) {
        case RendererAPI::API::None:
            SW_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
    }

    SW_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

}  // namespace Sword