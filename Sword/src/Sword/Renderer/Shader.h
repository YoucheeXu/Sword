#ifndef SHADER_H
#define SHADER_H

#pragma once

#include <string>

namespace Sword {

class Shader {
public:
    virtual ~Shader() = default;

    virtual void Bind() const   = 0;
    virtual void Unbind() const = 0;

    // virtual void UploadVSRendererUniformBuffer() = 0;

    static Shader* Create(std::string const& vertexSrc, std::string const& fragmentSrc);
};

}  // namespace Sword

#endif