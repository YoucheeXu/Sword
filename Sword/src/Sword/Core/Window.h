#ifndef DC87C5F0_573E_401C_8BD7_11AACC58C331
#define DC87C5F0_573E_401C_8BD7_11AACC58C331

#include <string>

#include "Sword/Core/Base.h"
#include "Sword/Events/Event.h"

namespace Sword {
struct WindowProps {
    std::string  Title;
    unsigned int Width;
    unsigned int Height;
    WindowProps(std::string const& title = "Sword Engine", unsigned int width = 1280, unsigned int height = 720)
        : Title(title), Width(width), Height(height) {}
};

// Interface representing a desktop system based Window
class SWORD_API Window {
public:
    using EventCallbackFn = std::function<void(Event&)>;

    virtual ~Window() = default;

    virtual void OnUpdate() = 0;

    virtual unsigned int GetWidth() const  = 0;
    virtual unsigned int GetHeight() const = 0;

    // Window attributes
    virtual void SetEventCallback(EventCallbackFn const& callback) = 0;
    virtual void SetVSync(bool enabled)                            = 0;
    virtual bool IsVSync() const                                   = 0;

    virtual void* GetNativeWindow() const = 0;

    static Window* Create(WindowProps const& props = WindowProps());
};
}  // namespace Sword

#endif /* DC87C5F0_573E_401C_8BD7_11AACC58C331 */
