#ifndef SANDBOX2D_H
#define SANDBOX2D_H

#pragma once

#include "Sword.h"

class Sandbox2D : public Sword::Layer {
public:
    Sandbox2D();
    ~Sandbox2D();

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    virtual void OnUpdate(Sword::TimeStep ts) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(Sword::Event& event) override;

private:
    Sword::OrthographicCameraController m_CameraController;

    Sword::Ref<Sword::Shader>      m_FlatColorShader;
    Sword::Ref<Sword::VertexArray> m_SquareVertexArray;

    Sword::Ref<Sword::Texture2D>   m_CheckboardTexture;

    glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};
};

#endif