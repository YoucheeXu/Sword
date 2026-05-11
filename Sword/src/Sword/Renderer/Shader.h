#ifndef SHADER_H
#define SHADER_H

#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <string>
#include <cstdint>

namespace Sword {

class Shader {
public:
    Shader(std::string const& vertexSrc, std::string const& fragmentSrc);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void UploadUniformMat4(std::string const& name, glm::mat4 const& matrix);

private:
    uint32_t m_RendererID;
};

}  // namespace Sword

#endif