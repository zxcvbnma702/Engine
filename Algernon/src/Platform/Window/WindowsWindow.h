#pragma once

#include "Algernon/Core/Window.h"

#include "Algernon/Renderer/GraphicsContext.h"
#include <GLFW/glfw3.h>

namespace Algernon {
	class WindowsWindow : public Window
	{
	private:
		// Windows subject
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	private:
		//Use glfw to init a window
		virtual void Init(const WindowProps& props);
		virtual void ShutDown();

	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline virtual void* GetNativeWindow() const { return m_Window; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync()const override;
	};
}
