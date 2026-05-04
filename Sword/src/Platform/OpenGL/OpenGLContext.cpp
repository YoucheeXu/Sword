#include "OpenGLContext.h"

#include "Sword/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Sword {

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {
    SW_CORE_ASSERT(windowHandle, "Window handle is null!");
}

OpenGLContext::~OpenGLContext() {}

void OpenGLContext::Init() {
    glfwMakeContextCurrent(m_WindowHandle);
    int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    SW_CORE_ASSERT(gladStatus, "Failed to initialize GLAD!");
}

void OpenGLContext::SwapBuffers() {
    glfwSwapBuffers(m_WindowHandle);
}

}  // namespace Sword