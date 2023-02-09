#pragma once
#include "Core.h"
#include "Window.h"
#include "LayerStack.h"

#include "hazel\events\Event.h"
#include "hazel\events\AppEvent.h"
#include "hazel\imgui\ImGuiLayer.h"
#include "hazel\renderer\Shader.h"
#include "hazel\renderer\Buffer.h"
#include "hazel\renderer\VertexArray.h"
#include "hazel\renderer\Camera.h"

namespace Hazel {

	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Run();
		virtual void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlayer(Layer* overlayer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		static Application* s_Instance;
		bool m_Running, m_Minimized = false;
		float m_LastFrameTime = 0.0f;
		
		LayerStack m_LayerStack;		
		ImGuiLayer* m_ImGuiLayer;
		std::unique_ptr<Window> m_Window;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
