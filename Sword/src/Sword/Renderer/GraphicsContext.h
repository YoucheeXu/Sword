#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H

#pragma once

namespace Sword {

class GraphicsContext {
public:
    GraphicsContext();
    ~GraphicsContext();

public:
    virtual void Init()        = 0;
    virtual void SwapBuffers() = 0;

private:
};

}  // namespace Sword

#endif