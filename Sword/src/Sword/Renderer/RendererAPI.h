#ifndef RENDERERAPI_H
#define RENDERERAPI_H

#pragma once

#include "Sword/Renderer/VertexArray.h"

#include <memory>
#include <glm/glm.hpp>

namespace Sword {

class RendererAPI {
public:
    enum class API { None = 0, OpenGL = 1 };

public:
    virtual ~RendererAPI() = default;

    virtual void Init() = 0;

    virtual void SetClearColor(glm::vec4 const& color) = 0;
    virtual void Clear()                               = 0;

    virtual void DrawIndexed(std::shared_ptr<VertexArray> const& vertexArray, uint32_t indexCount = 0) = 0;

    inline static API GetAPI() {
        return s_API;
    }

private:
    static API s_API;
};

}  // namespace Sword

#endif