#ifndef RENDERER2D_H
#define RENDERER2D_H

#pragma once

#include <glm/ext/vector_float2.hpp>

#include "OrthographicCamera.h"
#include "Sword/Renderer/Texture.h"

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
    static void DrawQuad(glm::vec2 const& position, glm::vec2 const& size, glm::vec4 const& color);
    static void DrawQuad(glm::vec3 const& position, glm::vec2 const& size, glm::vec4 const& color);
    static void DrawQuad(glm::vec2 const& position, glm::vec2 const& size, Ref<Texture2D> const& texture);
    static void DrawQuad(glm::vec3 const& position, glm::vec2 const& size, Ref<Texture2D> const& texture);

private:
};

}  // namespace Sword

#endif