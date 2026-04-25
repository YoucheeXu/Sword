#ifndef BF3CEA0A_F9A0_4258_A256_576901A73083
#define BF3CEA0A_F9A0_4258_A256_576901A73083

#include "Event.h"

#include <sstream>

namespace Sword {
class SWORD_API KeyEvent : public Event {
public:
    inline int GetKeyCode() const {
        return m_KeyCode;
    }
    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

protected:
    KeyEvent(int keycode) : m_KeyCode(keycode) {}
    int m_KeyCode;
};

class SWORD_API KeyPressedEvent : public KeyEvent {
public:
    KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}
    inline int GetRepeatCount() const {
        return m_RepeatCount;
    }

    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyPressedEvent:" << m_KeyCode << "()" << m_RepeatCount << "repeats)";
        return ss.str();
    }
    EVENT_CLASS_TYPE(KeyPressed)

private:
    int m_RepeatCount;
};

class SWORD_API KeyReleasedEvent : public KeyEvent {
public:
    KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}
    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyReleasedEvent:" << m_KeyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased);
};

class SWORD_API KeyTypedEvent : public KeyEvent {
public:
    KeyTypedEvent(int keycode) : KeyEvent(keycode) {}
    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyTypedEvent:" << m_KeyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyTyped);
};

}  // namespace Sword

#endif /* BF3CEA0A_F9A0_4258_A256_576901A73083 */
