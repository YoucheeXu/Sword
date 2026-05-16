#ifndef SHADER_H
#define SHADER_H

#pragma once

#include <string>
#include <unordered_map>

#include "Sword/Core/Base.h"

namespace Sword {

class Shader {
public:
    virtual ~Shader() = default;

    virtual void Bind() const   = 0;
    virtual void Unbind() const = 0;

    virtual std::string const& GetName() const = 0;

    // virtual void UploadVSRendererUniformBuffer() = 0;

    static Ref<Shader> Create(std::string const& filepath);
    static Ref<Shader> Create(std::string const& name, std::string const& vertexSrc, std::string const& fragmentSrc);
};

class ShaderLibrary {
public:
    void Add(std::string const& name, Ref<Shader> const& shader);
    void Add(Ref<Shader> const& shader);

    Ref<Shader> Load(std::string const& filepath);
    Ref<Shader> Load(std::string const& name, std::string const& filepath);

    Ref<Shader> Get(std::string const& name);

    bool Exists(std::string const& name) const;

private:
    std::unordered_map<std::string, Ref<Shader>> m_Shaders;
};

}  // namespace Sword

#endif