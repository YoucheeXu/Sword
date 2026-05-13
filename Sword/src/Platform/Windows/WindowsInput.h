#ifndef WINDOWSINPUT_H
#define WINDOWSINPUT_H

#pragma once

#include "Sword/Core/Input.h"

namespace Sword {

class WindowsInput : public Input {
public:
    WindowsInput();
    ~WindowsInput();

protected:
    virtual bool IsKeyPressedImpl(int keycode) override;
    virtual bool IsMouseButtonPressedImpl(int button) override;

    virtual std::pair<float, float> GetMousePositionImpl() override;
    virtual float                   GetMouseXImpl() override;
    virtual float                   GetMouseYImpl() override;

private:
};

}  // namespace Sword

#endif