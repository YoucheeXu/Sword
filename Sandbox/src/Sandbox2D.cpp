#include "Sandbox2D.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"
#include "glm/ext/matrix_float4x4.hpp"

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f), m_SquareColor({0.2f, 0.3f, 0.8f, 1.0f}) {}

Sandbox2D::~Sandbox2D() {}

void Sandbox2D::OnAttach() {
    m_SquareVertexArray = Sword::VertexArray::Create();

    // Vertex Buffer
    /* clang-format off */
    float squareVertices[3 * 4] = {
        -0.5f, -0.5f,   0.0f,
         0.5f, -0.5f,   0.0f,
         0.5f,  0.5f,  0.0f,
        -0.5f, 0.5f, 0.0f
    };
    /* clang-format on */

    std::shared_ptr<Sword::VertexBuffer> squareVertexBuffer;
    squareVertexBuffer.reset(Sword::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

    Sword::BufferLayout SquareLayout = {
        {Sword::ShaderDataType::Float3, "a_Position"},
    };
    squareVertexBuffer->SetLayout(SquareLayout);
    m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

    // Index Buffer
    unsigned int                   squareIndices[6] = {0, 1, 2, 2, 3, 0};
    Sword::Ref<Sword::IndexBuffer> squareIndexBuffer;
    squareIndexBuffer.reset(Sword::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
    m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

    m_FlatColorShader = Sword::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach() {}

void Sandbox2D::OnUpdate(Sword::TimeStep ts) {
    // Update
    m_CameraController.OnUpdate(ts);

    // Render
    Sword::RenderCommand::SetClearColor({0.1, 0.1, 0.1, 1});
    Sword::RenderCommand::Clear();

    Sword::Renderer::BeginScene(m_CameraController.GetCamera());

    std::dynamic_pointer_cast<Sword::OpenGLShader>(m_FlatColorShader)->Bind();
    std::dynamic_pointer_cast<Sword::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

    m_FlatColorShader->Bind();
    Sword::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    Sword::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(Sword::Event& event) {}