#pragma once

#include "Core.h"
#include "Event/Event.h"
#include "Window.h"
#include "Event/ApplicationEvent.h"
#include "LayerStack.h"

namespace Algernon {
	class ALGERNON_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:

		// Window close callback function
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	//To be defined in Client
	Application* CreateApplication();
}
