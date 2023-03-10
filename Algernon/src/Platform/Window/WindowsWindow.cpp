#include "Alpch.h"
#include "WindowsWindow.h"

#include "Algernon/Event/ApplicationEvent.h"
#include "Algernon/Event/KeyEvent.h"
#include "Algernon/Event/MouseEvent.h"
#include "Platform/OpenGL/OpenGLContext.h"
#include "Algernon/Core/Input.h"

namespace Algernon
{
	//static bool s_GLFWInitialized = false;
	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		AL_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	/*Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}*/

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		AL_PROFILE_FUNCTION();

		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		AL_PROFILE_FUNCTION();

		ShutDown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		AL_PROFILE_FUNCTION();

		//Set attribute of Windows
		m_Data.Title = props.Title;
		m_Data.Height = props.Height;
		m_Data.Width = props.Width;

		AL_CORE_INFO("Create Window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (s_GLFWWindowCount == 0)
		{
			AL_PROFILE_FUNCTION();

			int success = glfwInit();
			AL_CORE_ASSERT(success, "Could not intialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);
		}

		//Create a window window
		{
			AL_PROFILE_SCOPE("glfwCreateWindow")
			m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
			++s_GLFWWindowCount;
		}


		m_Context = CreateScope<OpenGLContext>(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks. The window data is obtained through the callback function of the GLFW library, 
		// and the window data is passed to the custom event in the callback function
		// 
		// Window
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		        data.Height = height;
		        data.Width = width;

		        WindowResizeEvent event(width, height);
				data.EventCallback(event);
			}
		);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		        WindowCloseEvent event;
		        data.EventCallback(event);
			}
		);
		//Keybord
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		        switch (action)
		        {
				case GLFW_PRESS:
				{
					KeyPressedEvent event(static_cast<KeyCode>(key), 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(static_cast<KeyCode>(key));
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(static_cast<KeyCode>(key), 1);
					data.EventCallback(event);
					break;
				}
				}
			}
		);
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		        KeyTypedEvent event(static_cast<KeyCode>(keycode));
		        data.EventCallback(event);
			});
		//Mouse
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		        switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(static_cast<MouseCode>(button));
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
					data.EventCallback(event);
					break;
				}
				}
			}
		);

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		        MouseScrolledEvent event((float)xOffset, (float)yOffset);
		        data.EventCallback(event);
			}
		);

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		        MouseMovedEvent event((float)xPos, (float)yPos);
		        data.EventCallback(event);
			}
		);
	}

	void WindowsWindow::ShutDown()
	{
		AL_PROFILE_FUNCTION();

		glfwDestroyWindow(m_Window);

		if (--s_GLFWWindowCount == 0)
		{
			AL_CORE_INFO("Terminating GLFW");
			glfwTerminate();
		}
	}

	void WindowsWindow::OnUpdate()
	{
		AL_PROFILE_FUNCTION();

		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		AL_PROFILE_FUNCTION();

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}