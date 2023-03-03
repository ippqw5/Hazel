#include "hzpch.h"
#include "OpenGLContext.h"

namespace Hazel {
	OpenGLContext::OpenGLContext(GLFWwindow* windowhandle)
		: m_Windowhandle(windowhandle)
	{
		HZ_CORE_ASSERT(windowhandle, "window handle is Null!");
	}

	void OpenGLContext::Init()
	{
		HZ_PROFILE_FUNCTION();
		glfwMakeContextCurrent(m_Windowhandle);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize Glad!");

		HZ_CORE_INFO("OpenGL Info: ");
		HZ_CORE_INFO("  Vendor: {0} ",(const char*)glGetString(GL_VENDOR));
		HZ_CORE_INFO("  Renderer: {0} ", (const char*)glGetString(GL_RENDERER));
		HZ_CORE_INFO("  Version: {0} ", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		HZ_PROFILE_FUNCTION();
		glfwSwapBuffers(m_Windowhandle);
	}

}