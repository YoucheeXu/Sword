#ifndef A84F02A0_CB1A_4EE9_91D1_7EC4B89F690B
#define A84F02A0_CB1A_4EE9_91D1_7EC4B89F690B

#include <cstdint>

namespace Sword {
using MouseCode = uint16_t;

namespace Mouse {
    enum : MouseCode {
        Button0 = 0,
        Button1 = 1,
        Button2 = 2,
        Button3 = 3,
        Button4 = 4,
        Button5 = 5,
        Button6 = 6,
        Button7 = 7,

        ButtonLast   = Button7,
        ButtonLeft   = Button0,
        ButtonRight  = Button1,
        ButtonMiddle = Button2
    };
}  // namespace Mouse
}  // namespace Sword

#endif /* A84F02A0_CB1A_4EE9_91D1_7EC4B89F690B */
