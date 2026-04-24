#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#pragma once

#include "Sword/Layer.h"

namespace Sword {

class SWORD_API ImGuiLayer : public Layer {
public:
    ImGuiLayer();
    ~ImGuiLayer();

    void OnAttach();
    void OnDetach();
    void OnUpdate();
    void OnEvent(Event& event);

private:
    float m_Time = 0.0f;
};

}  // namespace Sword

#endif