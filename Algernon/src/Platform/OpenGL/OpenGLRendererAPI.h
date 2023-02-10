#pragma once

#include "Algernon/Renderer/RendererAPI.h"

namespace Algernon
{
	class OpenGLRendererAPI: public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};

}


