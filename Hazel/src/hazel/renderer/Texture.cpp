#include "hzpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform\OpenGL\OpenGLTexture.h"

namespace Hazel {

	Ref<Texture2D> Texture2D::Create(const std::string& path, int c)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None :
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
		case RendererAPI::API::OpenGL :
			return std::make_shared<OpenGLTexture2D>(path, c);
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}