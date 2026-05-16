#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Sword/Core/Assert.h"

namespace Sword {

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {
    SW_CORE_ASSERT(windowHandle, "Window handle is null!");
}

OpenGLContext::~OpenGLContext() {}

void OpenGLContext::Init() {
    glfwMakeContextCurrent(m_WindowHandle);
    int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    SW_CORE_ASSERT(gladStatus, "Failed to initialize GLAD!");

    SW_CORE_INFO("OpenGL Info: ");
    SW_CORE_INFO("    Vender: {0}", reinterpret_cast<char const*>(glGetString(GL_VENDOR)));
    SW_CORE_INFO("    Render: {0}", reinterpret_cast<char const*>(glGetString(GL_RENDERER)));
    SW_CORE_INFO("    Version: {0}", reinterpret_cast<char const*>(glGetString(GL_VERSION)));
}

void OpenGLContext::SwapBuffers() {
    glfwSwapBuffers(m_WindowHandle);
}

}  // namespace Sword