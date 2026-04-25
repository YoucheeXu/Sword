#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#pragma once

#include "Sword/Layer.h"
#include "Sword/Events/KeyEvent.h"
#include "Sword/Events/MouseEvent.h"
#include "Sword/Events/ApplicationEvent.h"

namespace Sword {

class SWORD_API ImGuiLayer : public Layer {
public:
    ImGuiLayer();
    ~ImGuiLayer();

    void OnAttach();
    void OnDetach();
    void OnUpdate();
    void OnEvent(Event& event);

private:
    bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
    bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
    bool OnMouseMovedEvent(MouseMovedEvent& e);
    bool OnMouseScrolledEvent(MouseScrolledEvent& e);
    bool OnKeyPressedEvent(KeyPressedEvent& e);
    bool OnKeyReleasedEvent(KeyReleasedEvent& e);
    bool OnKeyTypedEvent(KeyTypedEvent& e);
    bool OnWindowResizedEvent(WindowResizeEvent& e);

private:
    float m_Time = 0.0f;
};

}  // namespace Sword

#endif