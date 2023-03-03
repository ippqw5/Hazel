#pragma once

#include "hazel\Core\Window.h"
#include "hazel\renderer\Camera.h"
#include "Platform\OpenGL\OpenGLContext.h"

#include <GLFW\glfw3.h>


namespace Hazel {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		//Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override
		{
			m_Data.EventCallback = callback;
		}
		void SetSync(bool enabled) override;
		bool IsVSync() const override;
		void LockSwitch() override;
		

		inline void* GetNativeWindow() const override { return m_Window; };

	private:
		virtual void Init(const WindowProperties& props);
		virtual void Shutdown();
	private:
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};
	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;
		WindowData m_Data;
			
		bool m_Lock = true;
		
	};
}