#include "Renderer.h"

namespace Sword {

Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::BeginScene(OrthographicCamera const& camera) {
    s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene() {}

void Renderer::Submit(std::shared_ptr<Shader> const&      shader,
                      std::shared_ptr<VertexArray> const& vertexArray,
                      glm::mat4 const&                    transform) {
    shader->Bind();
    shader->UploadUniformMat4("m_ViewProjection", s_SceneData->ViewProjectionMatrix);
    shader->UploadUniformMat4("m_Transform", transform);

    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
}

}  // namespace Sword