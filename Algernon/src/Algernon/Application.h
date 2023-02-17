#pragma once

#include "Core.h"
#include "Event/Event.h"
#include "Window.h"
#include "Event/ApplicationEvent.h"
#include "LayerStack.h"
#include "Algernon/ImGui/ImGuiLayer.h"
#include "Algernon/Core/Timestep.h"

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

		//Return abstract window, platform-independent
		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:

		// Window close callback function
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;

		Timestep m_Timestep;

		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};
	//To be defined in Client
	Application* CreateApplication();
}