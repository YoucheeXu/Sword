#include "Renderer.h"

namespace Sword {

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::BeginScene() {}

void Renderer::EndScene() {}

void Renderer::Submit(std::shared_ptr<Shader> const&      shader,
                      std::shared_ptr<VertexArray> const& vertexArray,
                      glm::mat4 const&                    transform) {
    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
}

}  // namespace Sword