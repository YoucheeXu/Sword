#ifndef B33512D9_1515_4CD8_9044_84E3EBE08700
#define B33512D9_1515_4CD8_9044_84E3EBE08700

#include <memory>
#include <cassert>

#ifdef SW_PLATFORM_WINDOWS
#    ifdef SW_BUILD_DLL
#        define SWORD_API __declspec(dllexport)
#    else
#        define SWORD_API __declspec(dllimport)
#    endif
#else
#    error Sword only support Windows!
#endif

#ifdef SW_DEBUG
#    if defined(SW_PLATFORM_WINDOWS)
// #        define SW_DEBUGBREAK() __debugbreak()
#        define SW_DEBUGBREAK() assert(false)
#    elif defined(SW_PLATFORM_LINUX)
#        include <signal.h>
#        define SW_DEBUGBREAK() raise(SIGTRAP)
#    else
#        error "Platform doesn't support debugbreak yet!"
#    endif
#    define SW_ENABLE_ASSERTS
#else
#    define SW_DEBUGBREAK()
#endif

#define BIT(x) (1 << x)

#define SW_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Sword {

template <typename T>
using Scope = std::unique_ptr<T>;

template <typename T>
using Ref = std::shared_ptr<T>;

}  // namespace Sword

#endif /* B33512D9_1515_4CD8_9044_84E3EBE08700 */
