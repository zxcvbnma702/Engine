#pragma once

#ifdef AL_PLATFORM_WINDOWS
#ifdef AL_BUILD_DLL
#define ALGERNON_API __declspec(dllexport)
#else
#define ALGERNON_API __declspec(dllimport)
#endif
#else
#error Algernon only support Windows!
#endif // AL_PLATFORM_WINDOWS

#define BIT(x) (1 << x)
