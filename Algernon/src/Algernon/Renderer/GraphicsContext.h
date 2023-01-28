#pragma once

namespace Algernon
{
	//Renderer Abstract Class
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}