#include "Application.h"

#include "Sword/Events/ApplicationEvent.h"
#include "Sword/Log.h"
#include "Sword/Window.h"

#include <memory>

#include <GLFW/glfw3.h>

namespace Sword {

Application::Application() {
    m_Window = std::unique_ptr<Window>(Window::Create());
}

Application::~Application() {}

[[noreturn]] void Application::Run() {
    WindowResizeEvent e(1980, 720);
    SW_TRACE(e.ToString());

    while (m_Running) {
        glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        m_Window->OnUpdate();
    }
}

}  // namespace Sword