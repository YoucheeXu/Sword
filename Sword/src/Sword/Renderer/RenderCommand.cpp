#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Sword {

// RendererAPI* RenderCommand::s_RendererAPI = RendererAPI::Create();
RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}  // namespace Sword