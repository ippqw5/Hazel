#include "hzpch.h"
#include "Platform/Windows/WindowsWindow.h"

#include "Hazel/Events/AppEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/KeyEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"
namespace Hazel {
	
	static void GLFWErrorCallback(int error, const char* description)
	{
		HZ_CORE_ERROR("GLFW Error ({0}) : {1} ", error, description);
	}

	static uint32_t s_GLFWWindowCount = 0;

	Scope<Window> Window::Create(const WindowProperties& props)
	{
		return CreateScope<WindowsWindow>(props);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& props)
	{
		HZ_PROFILE_FUNCTION();
		Init(props);
	}

	void WindowsWindow::Init(const WindowProperties& props)
	{

		m_Data.Title = props.Title;
		m_Data.Height = props.Height;
		m_Data.Width = props.Width;
		
		HZ_CORE_INFO("Creating Window... {0} ({1} {2})", props.Title, props.Width, props.Height);
		

		if (s_GLFWWindowCount==0)
		{
			// ToDo: glfwTerminate on system shutdown
			{
				HZ_PROFILE_SCOPE("glfwInit")
				int success = glfwInit();
				HZ_CORE_ASSERT(success, "Could not intialize GLFW!");
				glfwSetErrorCallback(GLFWErrorCallback);
			}
		}

		{
			HZ_PROFILE_SCOPE("glfwCreateWindow")
			m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
			++s_GLFWWindowCount;
		}

		//
		// glfwMakeContextCurrent(m_Window);
		//
		m_Context = GraphicsContext::Create(m_Window);
		m_Context->Init();

		
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetSync(true);

		//Set glfw callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowCloseEvent e;
				data.EventCallback(e);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent e(key, 0);
						data.EventCallback(e);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent e(key);
						data.EventCallback(e);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent e(key, 1);
						data.EventCallback(e);
						break;
					}
				}
		});
		
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent e(keycode);
				data.EventCallback(e);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent e(button);
						data.EventCallback(e);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent e(button);
						data.EventCallback(e);
						break;
					}
				}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});

	}
	
	WindowsWindow::~WindowsWindow()
	{
		HZ_PROFILE_FUNCTION();
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		HZ_PROFILE_FUNCTION();

		glfwPollEvents();
		m_Context->SwapBuffers(); //glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetSync(bool enabled)
	{
		HZ_PROFILE_FUNCTION();

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WindowsWindow::LockSwitch()
	{
		if(m_Lock == true)
		{
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			m_Lock = false;
		}
		else
		{
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			m_Lock = true;
		}

	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
		--s_GLFWWindowCount;

		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}

}