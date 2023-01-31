#include "Alpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Algernon
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}