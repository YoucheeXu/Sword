#include "Application.h"

#include "Sword/Events/ApplicationEvent.h"
#include "Sword/Log.h"

namespace Sword {

Application::Application() {}

Application::~Application() {}

[[noreturn]] void Application::Run() {
    WindowResizeEvent e(1980, 720);
    SW_TRACE(e.ToString());

    while (true) {
    }
}

}  // namespace Sword