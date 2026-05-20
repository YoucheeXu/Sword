#ifndef RENDERERAPI_H
#define RENDERERAPI_H

#pragma once

#include <glm/fwd.hpp>

#include "Sword/Core/Base.h"
#include "Sword/Renderer/VertexArray.h"

namespace Sword {

class RendererAPI {
public:
    enum class API { None = 0, OpenGL = 1 };

public:
    virtual ~RendererAPI() = default;

    virtual void Init() = 0;

    virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
    virtual void SetClearColor(glm::vec4 const& color) = 0;
    virtual void Clear()                               = 0;

    virtual void DrawIndexed(Ref<VertexArray> const& vertexArray, uint32_t indexCount = 0) = 0;

    inline static API GetAPI() {
        return s_API;
    }

private:
    static API s_API;
};

}  // namespace Sword

#endif