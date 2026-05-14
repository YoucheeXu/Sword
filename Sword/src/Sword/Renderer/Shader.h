#ifndef SHADER_H
#define SHADER_H

#include "glm/ext/vector_float4.hpp"
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

    void UploadUniformFloat4(std::string const& name, glm::vec4 const& vec);
    void UploadUniformMat4(std::string const& name, glm::mat4 const& matrix);

private:
    uint32_t m_RendererID;
};

}  // namespace Sword

#endif