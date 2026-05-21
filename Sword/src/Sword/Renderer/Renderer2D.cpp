#include "Renderer2D.h"

#include "Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Sword/Renderer/VertexArray.h"
#include "Sword/Renderer/RenderCommand.h"
#include "glm/ext/matrix_float4x4.hpp"

namespace Sword {

Renderer2D::Renderer2D() {}

Renderer2D::~Renderer2D() {}

struct Renderer2DStorage {
    Ref<VertexArray> QuadVertexArray;
    Ref<Shader>      FlatColorShader;
};

static Renderer2DStorage* s_Data;

void Renderer2D::Init() {
    s_Data = new Renderer2DStorage();

    s_Data->QuadVertexArray = VertexArray::Create();

    // Vertex Buffer
    /* clang-format off */
    float squareVertices[3 * 4] = {
        -0.5f, -0.5f,  0.0f,
         0.5f, -0.5f,  0.0f,
         0.5f,  0.5f,  0.0f,
        -0.5f, 0.5f, 0.0f
    };
    /* clang-format on */

    std::shared_ptr<VertexBuffer> squareVertexBuffer;
    squareVertexBuffer.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

    BufferLayout SquareLayout = {
        {ShaderDataType::Float3, "a_Position"},
    };
    squareVertexBuffer->SetLayout(SquareLayout);
    s_Data->QuadVertexArray->AddVertexBuffer(squareVertexBuffer);

    // Index Buffer
    unsigned int     squareIndices[6] = {0, 1, 2, 2, 3, 0};
    Ref<IndexBuffer> squareIndexBuffer;
    squareIndexBuffer.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
    s_Data->QuadVertexArray->SetIndexBuffer(squareIndexBuffer);

    s_Data->FlatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");
}

void Renderer2D::Shutdown() {
    delete s_Data;
}

void Renderer2D::BeginScene(OrthographicCamera const& camera) {
    std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->Bind();
    std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)
        ->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
}

void Renderer2D::EndScene() {}

void Renderer2D::DrawQuad(glm::vec2 const& position, glm::vec2 const& size, glm::vec4 const& color) {
    DrawQuad({position.x, position.y, 0.0f}, size, color);
}

void Renderer2D::DrawQuad(glm::vec3 const& position, glm::vec2 const& size, glm::vec4 const& color) {
    std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->Bind();
    std::dynamic_pointer_cast<Sword::OpenGLShader>(s_Data->FlatColorShader)->UploadUniformFloat4("u_Color", color);

    s_Data->QuadVertexArray->Bind();
    RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
}

}  // namespace Sword