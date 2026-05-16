#include "Renderer.h"

#include <memory>

#include "Sword/Renderer/RenderCommand.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Sword {

Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

void Renderer::Init() {
    RenderCommand::Init();
}

void Renderer::BeginScene(OrthographicCamera const& camera) {
    s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene() {}

void Renderer::Submit(Ref<Shader> const& shader, Ref<VertexArray> const& vertexArray, glm::mat4 const& transform) {
    shader->Bind();

    // TODO
    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection",
                                                                       s_SceneData->ViewProjectionMatrix);
    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

    // mi.Bind();

    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
}

}  // namespace Sword