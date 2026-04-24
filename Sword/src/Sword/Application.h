#ifndef APPLICATION_H
#define APPLICATION_H
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

   private:
    std::unique_ptr<Window> m_Window;
    bool m_Running = true;
};

// To be defined in CLIENT
Application* CreateApplication();
}  // namespace Sword

#endif