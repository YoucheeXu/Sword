#ifndef RENDERCOMMAND_H
#define RENDERCOMMAND_H

#pragma once

#include "RendererAPI.h"

namespace Sword {

class RenderCommand {
public:
    inline static void SetClearColor(glm::vec4 const& color) {
        s_RendererAPI->SetClearColor(color);
    }

    inline static void Clear() {
        s_RendererAPI->Clear();
    }

    inline static void DrawIndexed(std::shared_ptr<VertexArray> const& vertexArray, uint32_t indexCount = 0) {
        s_RendererAPI->DrawIndexed(vertexArray, indexCount);
    }

private:
    static RendererAPI* s_RendererAPI;
};

}  // namespace Sword

#endif