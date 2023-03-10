#pragma once
#ifdef HZ_PLATFORM_WINDOWS
	#if HZ_DYNAMIC_LINK
		#ifdef HZ_BUILD_DLL
			#define HAZEL_API __declspec(dllexport)
		#else	
			#define HAZEL_API __declspec(dllimport)
		#endif // HZ_BUILD_DLL
	#else
		#define HAZEL_API
	#endif
#else
	#error Hazel only support Windows!
#endif

#define BIT(x) (1<<x)

#ifdef HZ_DEBUG 
	#ifdef HZ_ENABLE_ASSERTS
		#define HZ_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
		#define HZ_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#else
		#define HZ_ASSERT(x, ...) 
		#define HZ_CORE_ASSERT(x, ...) 
	#endif
#else
	#define HZ_ASSERT(x, ...) 
	#define HZ_CORE_ASSERT(x, ...) 
#endif

#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#include <memory>

namespace Hazel {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}