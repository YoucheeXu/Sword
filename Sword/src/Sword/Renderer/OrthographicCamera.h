#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H

#pragma once

#include <glm/ext/vector_float3.hpp>
#include <glm/ext/matrix_float4x4.hpp>

namespace Sword {

class OrthographicCamera {
public:
    OrthographicCamera(float left, float right, float bottom, float top);
    ~OrthographicCamera();

    void SetProjection(float left, float right, float bottom, float top);

    inline glm::vec3 const& GetPosition() const {
        return m_Position;
    }
    inline void SetPosition(glm::vec3 const& position) {
        m_Position = position;
        RecalculateViewMatrix();
    }

    inline float GetRotation() const {
        return m_Rotation;
    }
    inline void SetRotation(float rotation) {
        m_Rotation = rotation;
        RecalculateViewMatrix();
    }

    inline glm::mat4 const& GetProjectionMatrix() const {
        return m_ProjectionMatrix;
    }
    inline glm::mat4 const& GetViewMatrix() const {
        return m_ViewMatrix;
    }
    inline glm::mat4 const& GetViewProjectionMatrix() const {
        return m_ViewProjectionMatrix;
    }

private:
    void RecalculateViewMatrix();

private:
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ViewProjectionMatrix;

    glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
    float     m_Rotation = 0.0f;
};

}  // namespace Sword

#endif