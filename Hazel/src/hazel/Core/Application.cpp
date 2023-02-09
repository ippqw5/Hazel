#include "hzpch.h"
#include "Application.h"

#include "hazel\Core\Log.h"
#include "hazel\Core\Input.h"
#include "hazel\Core\KeyCodes.h"

#include "hazel\renderer\Renderer.h"

#include <GLFW\glfw3.h>
namespace Hazel {

	Application* Application::s_Instance = nullptr;
	Application::Application()
	{
		s_Instance = this;

		m_Window = std::unique_ptr<Window>( Window::Create() );
		m_Window->SetEventCallback(HZ_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlayer(m_ImGuiLayer);
		 
		m_Running = true;
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{	

		while (m_Running)
		{
			float currentFrameTime = (float)glfwGetTime();
			Timestep deltaTime = currentFrameTime - m_LastFrameTime;
			m_LastFrameTime = currentFrameTime;

			if (!m_Minimized)
			{
				for (auto layer : m_LayerStack)
					layer->OnUpdate(deltaTime);
			}
			
			m_ImGuiLayer->Begin();
			for (auto layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();			 
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispather(e);
		dispather.Dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Application::OnWindowClosed));
		dispather.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(Application::OnWindowResize));
		

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
		layer->OnAttach();
	}

	void Application::PushOverlayer(Layer* overlayer)
	{
		m_LayerStack.PushOverlayer(overlayer);
		overlayer->OnAttach();
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}