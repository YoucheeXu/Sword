#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Sword {

OpenGLRendererAPI::OpenGLRendererAPI()
{

}

OpenGLRendererAPI::~OpenGLRendererAPI()
{

}

void OpenGLRendererAPI::SetClearColor(glm::vec4 const& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::DrawIndexed(std::shared_ptr<VertexArray> const& vertexArray, uint32_t indexCount) {
    glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}

}