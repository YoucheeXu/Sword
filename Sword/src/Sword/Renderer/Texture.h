#ifndef TEXTURE_H
#define TEXTURE_H

#pragma once

#include <cstdint>
#include <string>

#include "Sword/Core/Base.h"

namespace Sword {

class Texture {
public:
    Texture() = default;
    virtual ~Texture() {}

    virtual uint32_t GetWidth() const  = 0;
    virtual uint32_t GetHeight() const = 0;

    virtual void SetData(void* data, uint32_t size) = 0;

    virtual void Bind(uint32_t slot = 0) = 0;

private:
};

class Texture2D : public Texture {
public:
    static Ref<Texture2D> Create(uint32_t width, uint32_t height);
    static Ref<Texture2D> Create(std::string const& path);
};

}  // namespace Sword

#endif