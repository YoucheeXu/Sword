#ifndef OPENGLTEXTURE_H
#define OPENGLTEXTURE_H

#include <cstdint>
#pragma once

#include "Sword/Renderer/Texture.h"

namespace Sword {

class OpenGLTexture2D : public Texture2D {
public:
    OpenGLTexture2D(std::string const& path);
    virtual ~OpenGLTexture2D();

    virtual uint32_t GetWidth() const override {
        return m_Width;
    }
    virtual uint32_t GetHeight() const override {
        return m_Height;
    }

    void Bind(uint32_t slot) override;

private:
    std::string m_Path;
    uint32_t    m_Width, m_Height;
    uint32_t    m_RendererID = 0;
};

}  // namespace Sword

#endif