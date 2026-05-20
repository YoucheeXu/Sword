#ifndef OPENGLRENDERERAPI_H
#define OPENGLRENDERERAPI_H

#pragma once

#include <glm/glm.hpp>

#include "Sword/Core/Base.h"
#include "Sword/Renderer/RendererAPI.h"

namespace Sword {

class OpenGLRendererAPI : public RendererAPI {
public:
    OpenGLRendererAPI();
    ~OpenGLRendererAPI();

    virtual void Init() override;

    virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
    virtual void SetClearColor(glm::vec4 const& color) override;
    virtual void Clear() override;

    virtual void DrawIndexed(Ref<VertexArray> const& vertexArray, uint32_t indexCount = 0) override;

private:
};

}  // namespace Sword

#endif