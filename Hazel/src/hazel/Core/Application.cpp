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

		HZ_PROFILE_FUNCTION();

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
		HZ_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	void Application::Run()
	{	

		HZ_PROFILE_FUNCTION();

		while (m_Running)
		{
			HZ_PROFILE_SCOPE("Application Run Loop");
			float currentFrameTime = (float)glfwGetTime();
			Timestep deltaTime = currentFrameTime - m_LastFrameTime;
			m_LastFrameTime = currentFrameTime;

			if (!m_Minimized)
			{
				{
					HZ_PROFILE_SCOPE("LayerStack OnUpdate");

					for (auto layer : m_LayerStack)
						layer->OnUpdate(deltaTime);
				}

				m_ImGuiLayer->Begin();
				{
					HZ_PROFILE_SCOPE("LayerStack-OnImGuiRender OnUpdate");

					for (auto layer : m_LayerStack)
						layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
			}
			
			m_Window->OnUpdate();			 
		}
	}

	void Application::OnEvent(Event& e)
	{
		HZ_PROFILE_FUNCTION();

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
		HZ_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlayer(Layer* overlayer)
	{
		HZ_PROFILE_FUNCTION();

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
		HZ_PROFILE_FUNCTION();
		 
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