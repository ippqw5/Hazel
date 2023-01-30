#pragma once

#include "RendererAPI.h"

namespace Hazel {
	
	class RenderCommend
	{
	public:
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
		static RendererAPI* s_RendererAPI;
	};
}