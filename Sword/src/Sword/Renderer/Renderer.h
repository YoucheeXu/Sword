#ifndef RENDERER_H
#define RENDERER_H

#pragma once

#include "Sword/Core/Base.h"
#include "Sword/Renderer/OrthographicCamera.h"
#include "Sword/Renderer/Shader.h"
#include "Sword/Renderer/VertexArray.h"
#include "Sword/Renderer/RendererAPI.h"

namespace Sword {

class Renderer {
public:
    static void Init();

    static void BeginScene(OrthographicCamera const& camera);
    static void EndScene();

    static void Submit(Ref<Shader> const&      shader,
                       Ref<VertexArray> const& vertexArray,
                       glm::mat4 const&        transform = glm::mat4(1.0f));

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