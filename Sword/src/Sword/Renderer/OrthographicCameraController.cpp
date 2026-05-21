#include "OrthographicCameraController.h"

#include "Sword/Core/Input.h"
#include "Sword/Core/KeyCodes.h"
#include "Sword/Core/Log.h"
#include "Sword/Events/Event.h"

namespace Sword {
OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
    : m_AspectRatio(aspectRatio),
      m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
      m_Rotation(rotation) {}

OrthographicCameraController::~OrthographicCameraController() {}

void OrthographicCameraController::OnUpdate(TimeStep ts) {
    // more smooth
    float translateSpeed = m_CameraTranslationSpeed * ts;
    if (Input::IsKeyPressed(Key::A)) {
        m_CameraPosition.x += translateSpeed;
    } else if (Input::IsKeyPressed(Key::D)) {
        m_CameraPosition.x -= translateSpeed;
    }

    if (Input::IsKeyPressed(Key::W)) {
        m_CameraPosition.y -= translateSpeed;
    } else if (Input::IsKeyPressed(Key::S)) {
        m_CameraPosition.y += translateSpeed;
    }

    if (m_Rotation) {
        float rotationSpeed = m_CameraRotationSpeed * ts;
        if (Input::IsKeyPressed(Key::Q)) {
            m_CameraRotation -= rotationSpeed;
        } else if (Input::IsKeyPressed(Key::E)) {
            m_CameraRotation += rotationSpeed;
        }

        m_Camera.SetRotation(m_CameraRotation);
    }

    m_Camera.SetPosition(m_CameraPosition);

    m_CameraTranslationSpeed = m_ZoomLevel;
}

void OrthographicCameraController::OnEvent(Event& e) {
    EventDispatcher dispathcer(e);
    dispathcer.Dispatch<MouseScrolledEvent>(SW_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
    // dispathcer.Dispatch<WindowResizeEvent>(SW_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
}

bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e) {
    m_ZoomLevel -= e.GetYoffset() * 0.25f;
    m_ZoomLevel  = std::min(m_ZoomLevel, 8.0f);
    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

    return false;
}

bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e) {
    m_AspectRatio -= (float)e.GetWidth() / (float)e.GetHeight();
    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

    return false;
}

}  // namespace Sword