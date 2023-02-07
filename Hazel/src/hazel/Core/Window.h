#pragma once
#include "hzpch.h"

#include "hazel\Core\Core.h"
#include "hazel\events\Event.h"
#include "hazel\renderer\Camera.h"
namespace Hazel 
{
	struct WindowProperties
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProperties(const std::string& title = "Hazel Engine",
			unsigned int width = 1200,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{

		}
	};

	// Interface representing a desktop system based Window
	class HAZEL_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		
		virtual ~Window() {}
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		virtual void LockSwitch() = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProperties& props = WindowProperties());

	};
}