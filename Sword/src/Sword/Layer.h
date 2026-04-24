#ifndef LAYER_H
#define LAYER_H

#pragma once

#include "Sword/Core.h"
#include "Sword/Events/Event.h"
#include <string>

namespace Sword {

class SWORD_API Layer {
public:
    Layer(std::string const& name = "Layer");
    virtual ~Layer();

    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnUpdate() {}
    virtual void OnEvent(Event& event) {}

    inline std::string const& GetName() const {
        return m_DebugName;
    }

protected:
    std::string m_DebugName;
};

}  // namespace Sword

#endif