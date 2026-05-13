#ifndef WINDOWWINDOW_H
#define WINDOWWINDOW_H

#pragma once

#include "Sword/Core/Window.h"
#include "Sword/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Sword {
class WindowsWindow : public Window {
public:
    WindowsWindow(WindowProps const& props);
    virtual ~WindowsWindow();
    void                OnUpdate() override;
    inline unsigned int GetWidth() const override {
        return m_Data.Width;
    }
    inline unsigned int GetHeight() const override {
        return m_Data.Height;
    }
    //Window attributes
    inline void SetEventCallback(EventCallbackFn const& callback) override {
        m_Data.EventCallback = callback;
    }
    void SetVSync(bool enabled) override;
    bool IsVSync() const override;

    inline virtual void* GetNativeWindow() const override {
        return m_Window;
    }

private:
    virtual void Init(WindowProps const& props);
    virtual void Shutdown();

private:
    GLFWwindow*      m_Window;
    GraphicsContext* m_Context;

    struct WindowData {
        std::string  Title;
        unsigned int Width, Height;
        bool         VSync;

        EventCallbackFn EventCallback;
    };

    WindowData m_Data;
};
}  // namespace Sword
#endif