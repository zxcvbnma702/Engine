#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Algernon/Event/Event.h"
#include "Algernon/Event/ApplicationEvent.h"

#include "Algernon/Core/Timestep.h"
#include "Algernon/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Algernon {
	class ALGERNON_API Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		//Return abstract window, platform-independent
		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:

		void Run();

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
		friend int ::main(int argc, char** argv);
	};
	//To be defined in Client
	Application* CreateApplication();
}