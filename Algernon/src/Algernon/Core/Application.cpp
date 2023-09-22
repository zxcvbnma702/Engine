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
		AL_PROFILE_FUNCTION();

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
		AL_PROFILE_FUNCTION();
	}

	//Main loop
	void Application::Run()
	{
		AL_PROFILE_FUNCTION();

		while (m_Running)
		{
			AL_PROFILE_SCOPE("RunLoop")

			float time = (float)glfwGetTime();
			Timestep timestap = time - m_LastFrameTime;
			m_LastFrameTime = time;

			//Render form bottom to top
			if (!m_Minimized) {

				{
					AL_PROFILE_SCOPE("LayerStack OnUpdate");

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(timestap);
				}

				m_ImGuiLayer->Begin();

				{
					AL_PROFILE_SCOPE("LayerStack OnImGuiRender");

					for (Layer* layer : m_LayerStack)
						layer->OnImGuiRender();
				}

				m_ImGuiLayer->End();
			}

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		AL_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		//Event dispatcher from top to bottom
		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled)
				break;
			(*it)->OnEvent(e);
		}
		/*for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}*/
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		AL_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetWidth() == 0) {
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

	void Application::PushLayer(Layer* layer)
	{
		AL_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		AL_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
}