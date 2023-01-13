#include "hzpch.h"
#include "Application.h"


#include "hazel/Log.h"

#include <GLFW\glfw3.h>



namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>( Window::Create() );
		m_Running = true;
		
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{	
		
		while (m_Running)
		{
			glClearColor(0.0f, 1.0f, 0.8f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			for (auto layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
			 
		}
	}

	void Application::OnEvent(Event& e)
	{
		//HZ_CORE_INFO("{0}", e);
		EventDispatcher dispather(e);
		dispather.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlayer(Layer* overlayer)
	{
		m_LayerStack.PushOverlayer(overlayer);
	}


	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}