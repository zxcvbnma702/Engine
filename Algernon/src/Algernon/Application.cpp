#include "Alpch.h"
#include "Application.h"


#include "Algernon/Renderer/Renderer.h"
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "Input.h"

namespace Algernon {
	// About std::function and std::bind, see this linking
	//(https://stackoverflow.com/questions/37636373/how-stdbind-works-with-member-functions)
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		AL_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		// Window ///////////////////////////////////////////////////////////////////////////////
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_Window->SetVSync(false);

		Renderer::Init();

		//Layer /////////////////////////////////////////////////////////////////////////////////
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		//Renderer //////////////////////////////////////////////////////////////////////////////
	}

	Application::~Application()
	{
	}

	//Main loop
	void Application::Run()
	{
		while (m_Running)
		{

			float time = (float)glfwGetTime();
			Timestep timestap = time - m_LastFrameTime;
			m_LastFrameTime = time;

			//Render form bottom to top
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestap);

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		//Event dispatcher from top to bottom
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}
}