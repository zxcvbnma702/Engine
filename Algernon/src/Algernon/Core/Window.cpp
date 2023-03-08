#include "Alpch.h"
#include "Algernon/Core/Window.h"

#ifdef AL_PLATFORM_WINDOWS
#include "Platform/Window/WindowsWindow.h"
#endif // AL_PLATFORM_WINDOWS

namespace Algernon {
	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef AL_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		AL_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}