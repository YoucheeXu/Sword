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

#define BIT(x) (1 << x)

#endif /* B33512D9_1515_4CD8_9044_84E3EBE08700 */
