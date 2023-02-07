#pragma once
#include "Core.h"
#include "Window.h"
#include "LayerStack.h"

#include "events/Event.h"
#include "events/AppEvent.h"
#include "imgui/ImGuiLayer.h"
#include "renderer/Shader.h"
#include "renderer/Buffer.h"
#include "renderer/VertexArray.h"
#include "renderer/Camera.h"

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
		bool m_Running, m_Minimized = false;
		float m_LastFrameTime = 0.0f;
		
		LayerStack m_LayerStack;		
		ImGuiLayer* m_ImGuiLayer;
		static Application* s_Instance;
		std::unique_ptr<Window> m_Window;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
