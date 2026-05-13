#ifndef APPLICATION_H
#define APPLICATION_H

#pragma once

#include "Sword/Core/Core.h"
#include "Sword/Events/Event.h"
#include "Sword/Events/ApplicationEvent.h"
#include "Sword/Core/Window.h"
#include "Sword/Core/Layer.h"
#include "Sword/Core/LayerStack.h"
#include "Sword/ImGui/ImGuiLayer.h"

#include <memory>

namespace Sword {

class SWORD_API Application {
public:
    Application();
    virtual ~Application();

    void Run();

    void OnEvent(Event& e);

    void PushLayer(Layer* layer);
    void PushOverLay(Layer* layer);

    inline static Application& Get() {
        return *s_Instance;
    }

    inline Window& GetWindow() {
        return *m_Window;
    }

private:
    bool OnWindowClose(WindowCloseEvent& e);

    std::unique_ptr<Window> m_Window;
    ImGuiLayer*             m_ImGuiLayer;
    bool                    m_Running = true;
    LayerStack              m_LayerStack;

    float m_LastFrameTime = 0.0f;

private:
    static Application* s_Instance;
};

// To be defined in CLIENT
Application* CreateApplication();
}  // namespace Sword

#endif