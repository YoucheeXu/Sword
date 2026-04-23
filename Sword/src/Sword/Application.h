#ifndef APPLICATION_H
#define APPLICATION_H

#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Sword {

class SWORD_API Application {
   public:
    Application();
    virtual ~Application();

    [[noreturn]] void Run();

   private:
};

// To be defined in CLIENT
Application* CreateApplication();
}  // namespace Sword

#endif