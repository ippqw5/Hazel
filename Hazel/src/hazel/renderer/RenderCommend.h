#pragma once

#include "RendererAPI.h"

namespace Hazel {
	
	class RenderCommend
	{
	public:
		static inline void Init()
		{
			s_RendererAPI->Init();
		}
		static inline void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}
		static inline void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}
		static inline void Clear()
		{
			s_RendererAPI->Clear();
		}
		static inline void DrawIndexed(const std::shared_ptr<VertexArray> vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}
	private:
		static Scope<RendererAPI> s_RendererAPI;
	};
}