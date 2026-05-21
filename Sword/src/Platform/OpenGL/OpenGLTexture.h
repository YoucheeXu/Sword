#ifndef OPENGLTEXTURE_H
#define OPENGLTEXTURE_H

#pragma once

#include <cstdint>
#include "OpenGLShader.h"

#include "Sword/Renderer/Texture.h"

namespace Sword {

class OpenGLTexture2D : public Texture2D {
public:
    OpenGLTexture2D(uint32_t width, uint32_t height);
    OpenGLTexture2D(std::string const& path);
    virtual ~OpenGLTexture2D();

    virtual uint32_t GetWidth() const override {
        return m_Width;
    }
    virtual uint32_t GetHeight() const override {
        return m_Height;
    }

    virtual void SetData(void* data, uint32_t size) override;

    virtual void Bind(uint32_t slot) override;

private:
    std::string m_Path;
    uint32_t    m_Width, m_Height;
    uint32_t    m_RendererID = 0;
    GLenum      m_InternalFormat, m_DataFormat;
};

}  // namespace Sword

#endif