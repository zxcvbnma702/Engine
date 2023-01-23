#pragma once

#include "Alpch.h"

#include "Core.h"
#include "Event/Event.h"

namespace Algernon
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Algernon", unsigned int width = 1280, unsigned int height = 720)
			:Title(title), Width(width), Height(height) {}
	};

	// Interface abstract class
	class ALGERNON_API Window
	{
	public:
		//Event callback function
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		//When the window update
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		//Return specific window
		virtual void* GetNativeWindow() const = 0;

		//Generic interface for creating windows
		static Window* Create(const WindowProps& props = WindowProps());
	};
}