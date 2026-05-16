#ifndef D49E75EF_47CE_46AE_8777_C7414D591C5B
#define D49E75EF_47CE_46AE_8777_C7414D591C5B

#include "Sword/Core/Core.h"
#include "Sword/Core/Log.h"

#ifdef SW_ENABLE_ASSERTS
#    define SW_ASSERT(x, ...)                                                                                          \
        {                                                                                                              \
            if (!(x)) {                                                                                                \
                SW_ERROR("Assertion Failed: {}", __VA_ARGS__);                                                          \
                SW_DEBUGBREAK();                                                                                       \
            }                                                                                                          \
        }
#    define SW_CORE_ASSERT(x, ...)                                                                                     \
        {                                                                                                              \
            if (!(x)) {                                                                                                \
                SW_CORE_ERROR("Assertion Failed: {}", __VA_ARGS__);                                                     \
                SW_DEBUGBREAK();                                                                                       \
            }                                                                                                          \
        }
#else
#    define SW_ASSERT(x, ...)
#    define SW_CORE_ASSERT(x, ...)
#endif

#endif /* D49E75EF_47CE_46AE_8777_C7414D591C5B */
