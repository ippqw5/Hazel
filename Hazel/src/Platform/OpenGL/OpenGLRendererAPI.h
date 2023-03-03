#pragma once

#include "hazel\renderer\RendererAPI.h"

namespace Hazel {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init();
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		virtual void SetClearColor(const glm::vec4& color);
		virtual void Clear();
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray);
	};
}