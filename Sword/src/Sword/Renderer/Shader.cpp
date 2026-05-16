#include "Shader.h"
#include "Sword/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <memory>

namespace Sword {
Ref<Shader> Shader::Create(std::string const& filepath) {
    switch (RendererAPI::GetAPI()) {
        case RendererAPI::API::None:
            SW_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filepath);
    }

    SW_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

Ref<Shader> Shader::Create(std::string const& name, std::string const& vertexSrc, std::string const& fragmentSrc) {
    switch (RendererAPI::GetAPI()) {
        case RendererAPI::API::None:
            SW_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
    }

    SW_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

void ShaderLibrary::Add(std::string const& name, Ref<Shader> const& shader) {
    SW_CORE_ASSERT(!Exists(name), "Shader already exists!");
    m_Shaders[name] = shader;
}

void ShaderLibrary::Add(Ref<Shader> const& shader) {
    auto& name = shader->GetName();
    Add(name, shader);
}

Ref<Shader> ShaderLibrary::Load(std::string const& filepath) {
    auto shader = Shader::Create(filepath);
    Add(shader);
    return shader;
}

Ref<Shader> ShaderLibrary::Load(std::string const& name, std::string const& filepath) {
    auto shader = Shader::Create(filepath);
    Add(name, shader);
    return shader;
}

Ref<Shader> ShaderLibrary::Get(std::string const& name) {
    SW_CORE_ASSERT(Exists(name), "Shader not found!");
    return m_Shaders[name];
}

bool ShaderLibrary::Exists(std::string const& name) const {
    return m_Shaders.find(name) != m_Shaders.end();
}

}  // namespace Sword