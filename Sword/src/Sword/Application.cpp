#include "Application.h"

#include "Events/Event.h"
#include "Sword/Events/ApplicationEvent.h"
#include "Sword/Log.h"
#include "Sword/Window.h"

#include <functional>
#include <memory>

#include <GLFW/glfw3.h>

namespace Sword {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

Application::Application() {
    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
}

Application::~Application() {}

void Application::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

    SW_CORE_TRACE(e.ToString());
}

[[noreturn]] void Application::Run() {
    WindowResizeEvent e(1980, 720);
    SW_TRACE(e.ToString());

    while (m_Running) {
        glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        m_Window->OnUpdate();
    }
}

bool Application::OnWindowClose(WindowCloseEvent& e) {
    m_Running = false;
    return true;
}

}  // namespace Sword