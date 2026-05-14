#ifndef OPENGLSHADER_H
#define OPENGLSHADER_H

#pragma once

#include "Sword/Renderer/Shader.h"

#include <glm/ext/matrix_float4x4.hpp>

namespace Sword {

class OpenGLShader : public Shader {
public:
    OpenGLShader(std::string const& vertexSrc, std::string const& fragmentSrc);
    virtual ~OpenGLShader();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    void UploadUniformInt(std::string const& name, int val);

    void UploadUniformFloat(std::string const& name, float val);
    void UploadUniformFloat2(std::string const& name, glm::vec2 const& vec);
    void UploadUniformFloat3(std::string const& name, glm::vec3 const& vec);
    void UploadUniformFloat4(std::string const& name, glm::vec4 const& vec);

    void UploadUniformMat3(std::string const& name, glm::mat3 const& matrix);
    void UploadUniformMat4(std::string const& name, glm::mat4 const& matrix);

private:
    uint32_t m_RendererID;
};

}  // namespace Sword

#endif