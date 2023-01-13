#pragma once
#include "Core.h"
#include "Window.h"
#include "LayerStack.h"

#include "events/Event.h"
#include "events/AppEvent.h"

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
	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running;
		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
