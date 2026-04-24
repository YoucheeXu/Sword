#ifndef APPLICATION_H
#define APPLICATION_H
#include "Sword/Events/ApplicationEvent.h"
#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Sword/Window.h"

#include <memory>

namespace Sword {

class SWORD_API Application {
public:
    Application();
    virtual ~Application();

    [[noreturn]] void Run();

    void OnEvent(Event& e);

private:
    bool OnWindowClose(WindowCloseEvent& e);

    std::unique_ptr<Window> m_Window;
    bool                    m_Running = true;
};

// To be defined in CLIENT
Application* CreateApplication();
}  // namespace Sword

#endif