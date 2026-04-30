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

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnEvent(Event& event) override;

    virtual void OnImGuiRender() override;

    void Begin();
    void End();

private:
    bool OnWindowResizedEvent(WindowResizeEvent& e);

private:
    float m_Time = 0.0f;
};

}  // namespace Sword

#endif