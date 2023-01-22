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

#ifdef AL_ENABLE_ASSERTS
#define AL_ASSERT(x, ...) { if(!(x)) { AL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define AL_CORE_ASSERT(x, ...) { if(!(x)) { AL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define AL_ASSERT(x, ...)
#define AL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define AL_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
