#ifndef OPENGLCONTEXT_H
#define OPENGLCONTEXT_H

#pragma once

#include "Sword/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Sword {

class OpenGLContext : public GraphicsContext {
public:
    OpenGLContext(GLFWwindow* windowHandle);
    ~OpenGLContext();

public:
    virtual void Init() override;
    virtual void SwapBuffers() override;

private:
    GLFWwindow* m_WindowHandle;
};

}  // namespace Sword

#endif