#ifndef RENDERER2D_H
#define RENDERER2D_H

#pragma once

#include "glm/ext/vector_float2.hpp"

#include "OrthographicCamera.h"

namespace Sword {

class Renderer2D {
public:
    Renderer2D();
    ~Renderer2D();

    static void Init();
    static void Shutdown();

    static void BeginScene(OrthographicCamera const& camera);
    static void EndScene();

    // Primitives
    static void DrawQuad(glm::vec2 const& position, const glm::vec2& size, const glm::vec4& color);
    static void DrawQuad(glm::vec3 const& position, const glm::vec2& size, const glm::vec4& color);

private:
};

}  // namespace Sword

#endif