#ifndef APPLICATION_H
#define APPLICATION_H

#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Sword/Events/ApplicationEvent.h"
#include "Sword/Window.h"
#include "Layer.h"
#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"
#include "Sword/Renderer/Shader.h"
#include "Sword/Renderer/Buffer.h"

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

    unsigned int                  m_VertexArray;
    std::unique_ptr<Shader>       m_Shader;
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    std::unique_ptr<IndexBuffer>  m_IndexBuffer;

private:
    static Application* s_Instance;
};

// To be defined in CLIENT
Application* CreateApplication();
}  // namespace Sword

#endif