#ifndef RENDERER_H
#define RENDERER_H

#pragma once

#include "Sword/Renderer/RenderCommand.h"
#include "Sword/Renderer/Shader.h"

#include <memory>

namespace Sword {

class Renderer {
public:
    Renderer();
    ~Renderer();

    static void BeginScene();
    static void EndScene();

    static void Submit(std::shared_ptr<Shader> const&      shader,
                       std::shared_ptr<VertexArray> const& vertexArray,
                       glm::mat4 const&                    transform = glm::mat4(1.0f));

    static RendererAPI::API GetAPI() {
        return RendererAPI::GetAPI();
    }

private:
};

}  // namespace Sword

#endif