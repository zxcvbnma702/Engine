#include "Alpch.h"
#include "Algernon/Core/Input.h"

#ifdef AL_PLATFORM_WINDOWS
#include "Platform/Window/WindowsInput.h"
#endif // AL_PLATFORM_WINDOWS

namespace Algernon {
	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
#ifdef AL_PLATFORM_WINDOWS
		return CreateScope<WindowsInput>();
#else
		AL_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}
