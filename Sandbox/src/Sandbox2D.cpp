#include "Sandbox2D.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"
#include "glm/ext/matrix_float4x4.hpp"

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f), m_SquareColor({0.2f, 0.3f, 0.8f, 1.0f}) {}

Sandbox2D::~Sandbox2D() {}

void Sandbox2D::OnAttach() {

}

void Sandbox2D::OnDetach() {}

void Sandbox2D::OnUpdate(Sword::TimeStep ts) {
    // Update
    m_CameraController.OnUpdate(ts);

    // Render
    Sword::RenderCommand::SetClearColor({0.1, 0.1, 0.1, 1});
    Sword::RenderCommand::Clear();

    Sword::Renderer2D::BeginScene(m_CameraController.GetCamera());

    Sword::Renderer2D::DrawQuad({0.0, 0.0f}, {1.0f, 1.0f}, {0.8f, 0.2f, 0.3f, 1.0f});

    Sword::Renderer2D::EndScene();

}

void Sandbox2D::OnImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(Sword::Event& event) {}