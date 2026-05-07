#ifndef RENDERERAPI_H
#define RENDERERAPI_H

#pragma once

namespace Sword {

class RendererAPI {
public:
    enum class API { None = 0, OpenGL = 1 };

public:
    virtual ~RendererAPI() = default;
    inline static API GetAPI() {
        return s_API;
    }

private:
    static API s_API;
};

}  // namespace Sword

#endif