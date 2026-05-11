#ifndef OPENGLRENDERERAPI_H
#define OPENGLRENDERERAPI_H

#pragma once

#include "Sword/Renderer/RendererAPI.h"

#include <memory>

namespace Sword {

class OpenGLRendererAPI : public RendererAPI {
public:
    OpenGLRendererAPI();
    ~OpenGLRendererAPI();

    virtual void SetClearColor(glm::vec4 const& color) override;
    virtual void Clear() override;

    virtual void DrawIndexed(std::shared_ptr<VertexArray> const& vertexArray, uint32_t indexCount = 0) override;

private:
};

}  // namespace Sword

#endif