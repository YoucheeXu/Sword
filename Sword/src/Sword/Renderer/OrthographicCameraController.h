#ifndef ORTHOGRAPHICCAMERACONTROLLER_H
#define ORTHOGRAPHICCAMERACONTROLLER_H

#pragma once

#include "Sword/Renderer/OrthographicCamera.h"
#include "Sword/Core/TimeStep.h"
#include "Sword/Events/MouseEvent.h"
#include "Sword/Events/ApplicationEvent.h"

namespace Sword {

class OrthographicCameraController {
public:
    OrthographicCameraController(float aspectRatio, bool rotation = false);
    ~OrthographicCameraController();

    void OnUpdate(TimeStep ts);
    void OnEvent(Event& e);

    OrthographicCamera& GetCamera() {
        return m_Camera;
    }
    OrthographicCamera const& GetCamera() const {
        return m_Camera;
    }

private:
    bool OnMouseScrolled(MouseScrolledEvent& e);
    bool OnWindowResized(WindowResizeEvent& e);

private:
    float m_AspectRatio;
    float m_ZoomLevel = 1.0f;

    OrthographicCamera m_Camera;

    bool m_Rotation;

    glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
    float     m_CameraRotation = 0.0f;  // In degrees, in the anti-clockwise direction

    float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
};

}  // namespace Sword

#endif