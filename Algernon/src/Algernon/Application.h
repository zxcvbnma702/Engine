#pragma once

#include "Core.h"
#include "Event/Event.h"

namespace Algernon {
	class ALGERNON_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in Client
	Application* CreateApplication();
}
