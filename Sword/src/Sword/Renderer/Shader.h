#ifndef SHADER_H
#define SHADER_H

#pragma once

#include <string>
#include <cstdint>

namespace Sword {

class Shader {
public:
    Shader(std::string const& vertexSrc, std::string const& fragmentSrc);
    ~Shader();

    void Bind() const;
    void Unbind() const;

private:
    uint32_t m_RendererID;
};

}  // namespace Sword

#endif