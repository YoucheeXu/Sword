#ifndef OPENGLSHADER_H
#define OPENGLSHADER_H

#pragma once

#include "Sword/Renderer/Shader.h"

#include <string>
#include <unordered_map>
#include <glm/ext/matrix_float4x4.hpp>

// TODO: remove
typedef unsigned int GLenum;

namespace Sword {

class OpenGLShader : public Shader {
public:
    OpenGLShader(std::string const& filepath);
    OpenGLShader(std::string const& name, std::string const& vertexSrc, std::string const& fragmentSrc);
    virtual ~OpenGLShader();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual std::string const& GetName() const override {
        return m_Name;
    }

    void UploadUniformInt(std::string const& name, int val);

    void UploadUniformFloat(std::string const& name, float val);
    void UploadUniformFloat2(std::string const& name, glm::vec2 const& vec);
    void UploadUniformFloat3(std::string const& name, glm::vec3 const& vec);
    void UploadUniformFloat4(std::string const& name, glm::vec4 const& vec);

    void UploadUniformMat3(std::string const& name, glm::mat3 const& matrix);
    void UploadUniformMat4(std::string const& name, glm::mat4 const& matrix);

private:
    std::string ReadFile(std::string const& filepath);

    std::unordered_map<GLenum, std::string> PreProcess(std::string const& source);

    void Compile(std::unordered_map<GLenum, std::string>& shaderSource);

private:
    uint32_t    m_RendererID;
    std::string m_Name;
};

}  // namespace Sword

#endif