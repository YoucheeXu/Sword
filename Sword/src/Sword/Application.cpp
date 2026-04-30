#include "Application.h"

#include "Events/Event.h"
#include "ImGui/ImGuiLayer.h"
#include "Sword/Events/ApplicationEvent.h"
#include "Sword/Log.h"
#include "Sword/Window.h"

#include <functional>
#include <memory>

#include <glad/glad.h>

namespace Sword {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

Application* Application::s_Instance = nullptr;

Application::Application() {
    SW_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

    m_ImGuiLayer = new ImGuiLayer();
    PushOverLay(m_ImGuiLayer);
}

Application::~Application() {
    delete m_ImGuiLayer;
}

void Application::PushLayer(Layer* layer) {
    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
}

void Application::PushOverLay(Layer* layer) {
    m_LayerStack.PushOverlay(layer);
    layer->OnAttach();
}

void Application::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

    SW_CORE_TRACE(e.ToString());

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
        (*--it)->OnEvent(e);
        if (e.Handled) {
            break;
        }
    }
}

void Application::Run() {
    WindowResizeEvent e(1980, 720);
    SW_TRACE(e.ToString());

    while (m_Running) {
        glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        for (Layer* layer : m_LayerStack) {
            layer->OnUpdate();
        }

        m_ImGuiLayer->Begin();
        for (Layer* layer : m_LayerStack) {
            layer->OnImGuiRender();
        }
        m_ImGuiLayer->End();

        m_Window->OnUpdate();
    }
}

bool Application::OnWindowClose(WindowCloseEvent& e) {
    m_Running = false;
    return true;
}

}  // namespace Sword