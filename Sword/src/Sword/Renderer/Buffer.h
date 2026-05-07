#ifndef BUFFER_H
#define BUFFER_H

#pragma once

#include <cstdint>

namespace Sword {

class VertexBuffer {
public:
    virtual ~VertexBuffer() = default;

    virtual void Bind() const   = 0;
    virtual void Unbind() const = 0;

    static VertexBuffer* Create(float* vertices, uint32_t size);

private:
};

class IndexBuffer {
public:
    virtual ~IndexBuffer() = default;

    virtual void Bind() const   = 0;
    virtual void Unbind() const = 0;

    virtual uint32_t GetCount() const = 0;

    static IndexBuffer* Create(uint32_t* indices, uint32_t count);

private:
};

}  // namespace Sword

#endif