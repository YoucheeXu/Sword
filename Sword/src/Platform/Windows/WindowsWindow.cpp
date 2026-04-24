#include "WindowsWindow.h"

#include "Sword/Log.h"

namespace Sword {

static bool s_GLFWInitialized = false;

Window* Window::Create(WindowProps const& props) {
    return new WindowsWindow(props);
}

WindowsWindow::WindowsWindow(WindowProps const& props) {
    Init(props);
}

WindowsWindow::~WindowsWindow() {
    Shutdown();
}

void WindowsWindow::Init(WindowProps const& props) {
    m_Data.Title  = props.Title;
    m_Data.Width  = props.Width;
    m_Data.Height = props.Height;

    SW_CORE_INFO("Creating window{0}({1},{2})", props.Title, props.Width, props.Height);

    if (!s_GLFWInitialized) {
        //ToDo:glfwTerminate on system shutdown
        int success = glfwInit();
        SW_CORE_ASSERT(success, "Could not intialize GLFW!");
        s_GLFWInitialized = true;
    }

    m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);
}

void WindowsWindow::Shutdown() {
    glfwDestroyWindow(m_Window);
}

void WindowsWindow::OnUpdate() {
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}

void WindowsWindow::SetVSync(bool enabled) {
    if (enabled) {
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }
    m_Data.VSync = enabled;
}

bool WindowsWindow::IsVSync() const {
    return m_Data.VSync;
}
}  // namespace Sword
