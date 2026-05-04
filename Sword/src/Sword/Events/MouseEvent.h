#ifndef F8A9D02F_21E5_4615_9BE4_2D645599CAB4
#define F8A9D02F_21E5_4615_9BE4_2D645599CAB4

#include "Event.h"

#include <sstream>

namespace Sword {
class SWORD_API MouseMovedEvent : public Event {
public:
    MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}
    inline float GetX() const {
        return m_MouseX;
    }
    inline float GetY() const {
        return m_MouseY;
    }
    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
        return ss.str();
    }
    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

private:
    float m_MouseX, m_MouseY;
};

class SWORD_API MouseScrolledEvent : public Event {
public:
    MouseScrolledEvent(float xoffset, float yoffset) : m_Xoffset(xoffset), m_Yoffset(yoffset) {}

    inline float GetXoffset() const {
        return m_Xoffset;
    }
    inline float GetYoffset() const {
        return m_Yoffset;
    }

    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << GetXoffset() << ", " << GetYoffset();
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

private:
    float m_Xoffset, m_Yoffset;
};

class SWORD_API MouseButtonEvent : public Event {
public:
    inline int GetMouseButton() const {
        return m_Button;
    }
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

protected:
    MouseButtonEvent(int button) : m_Button(button) {}
    int m_Button;
};

class SWORD_API MouseButtonPressedEvent : public MouseButtonEvent {
public:
    MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}
    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << m_Button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonPressed)
};

class SWORD_API MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << m_Button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonReleased)
};

}  // namespace Sword

#endif /* F8A9D02F_21E5_4615_9BE4_2D645599CAB4 */
