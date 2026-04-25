#ifndef B33512D9_1515_4CD8_9044_84E3EBE08700
#define B33512D9_1515_4CD8_9044_84E3EBE08700

#ifdef SW_PLATFORM_WINDOWS
#    ifdef SW_BUILD_DLL
#        define SWORD_API __declspec(dllexport)
#    else
#        define SWORD_API __declspec(dllimport)
#    endif
#else
#    error Sword only support Windows!
#endif

#ifdef SW_ENABLE_ASSERTS
#    define SW_ASSERT(x, ...)                                                                                          \
        {                                                                                                              \
            if (!(x)) {                                                                                                \
                SW_ERROR("Assertion Failed:{O}", __VA_ARGS__);                                                         \
                _debugbreak();                                                                                         \
            }                                                                                                          \
        }
#    define SW_CORE_ASSERT(x, ...)                                                                                     \
        {                                                                                                              \
            if (!(x)) {                                                                                                \
                SW_CORE_ERROR("Assertion Failed:{O}", __VA_ARGS__);                                                    \
                __debugbreak();                                                                                        \
            }                                                                                                          \
        }
#else
#    define SW_ASSERT(x, ...)
#    define SW_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define SW_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#endif /* B33512D9_1515_4CD8_9044_84E3EBE08700 */
