#include "hzpch.h"
#include "RenderCommend.h"

#include "Platform\OpenGL\OpenGLRendererAPI.h"

namespace Hazel {
	RendererAPI* RenderCommend::s_RendererAPI = new OpenGLRendererAPI;
}