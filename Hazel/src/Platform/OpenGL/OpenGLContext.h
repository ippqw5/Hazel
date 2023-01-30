#pragma once
#include "hazel\renderer\GraphicsContext.h"

#include <GLFW\glfw3.h>
#include <glad\glad.h>

namespace Hazel {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowhandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_Windowhandle;
	};
}