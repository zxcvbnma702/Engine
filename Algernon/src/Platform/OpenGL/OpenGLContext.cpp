#include "Alpch.h"
#include "OpenGlContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace Algernon {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		AL_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		AL_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		AL_CORE_ASSERT(status, "Failed to initialize Glad!");

		//AL_CORE_INFO("OpenGL Info:");
		/*AL_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));*/
		/*AL_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		AL_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));*/
	}

	void OpenGLContext::SwapBuffers()
	{
		AL_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}


}