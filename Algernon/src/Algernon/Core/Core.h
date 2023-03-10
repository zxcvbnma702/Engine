#pragma once

#include <memory>

#ifdef AL_PLATFORM_WINDOWS
#if AL_DYNAMIC_LINK
	#ifdef AL_BUILD_DLL
         #define ALGERNON_API __declspec(dllexport)
	#else
	     #define ALGERNON_API __declspec(dllimport)
	#endif
#else
    #define ALGERNON_API
#endif
#else
     #error Algernon only support Windows!
#endif // AL_PLATFORM_WINDOWS

#ifdef AL_DEBUG
#define AL_ENABLE_ASSERTS
#endif

#ifdef AL_ENABLE_ASSERTS
#define AL_ASSERT(x, ...) { if(!(x)) { AL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define AL_CORE_ASSERT(x, ...) { if(!(x)) { AL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define AL_ASSERT(x, ...)
#define AL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define AL_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Algernon
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
