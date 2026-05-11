#ifndef RENDERER_H
#define RENDERER_H

#include "glm/ext/vector_float4.hpp"
#pragma once

#include "OrthographicCamera.h"
#include "Sword/Renderer/RenderCommand.h"
#include "Sword/Renderer/Shader.h"

#include <memory>

namespace Sword {

class Renderer {
public:
    Renderer();
    ~Renderer();

    static void BeginScene(OrthographicCamera const& camera);
    static void EndScene();

    static void Submit(std::shared_ptr<Shader> const&      shader,
                       std::shared_ptr<VertexArray> const& vertexArray,
                       glm::mat4 const&                    transform = glm::mat4(1.0f));

    static RendererAPI::API GetAPI() {
        return RendererAPI::GetAPI();
    }

private:
    struct SceneData {
        glm::mat4 ViewProjectionMatrix;
    };

    static SceneData* s_SceneData;
};

}  // namespace Sword

#endif