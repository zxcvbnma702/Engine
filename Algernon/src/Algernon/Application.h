#pragma once

#include "Core.h"
#include "Event/Event.h"
#include "Window.h"
#include "Event/ApplicationEvent.h"
#include "LayerStack.h"
#include "Algernon/ImGui/ImGuiLayer.h"
#include "Algernon/Renderer/Shader.h"
#include "Algernon/Renderer/Buffer.h"
#include "Algernon/Renderer/VertexArray.h"

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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

	private:
		static Application* s_Instance;
	};
	//To be defined in Client
	Application* CreateApplication();
}