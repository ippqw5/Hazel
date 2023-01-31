#pragma once

#include "RenderCommend.h"
#include "Camera.h"
#include "Shader.h"

namespace Hazel {


	class Renderer
	{
	public:

		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader,const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& model = glm::mat4(1.0f));
		
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct Matrix_VP
		{
			glm::mat4 viewMatrix;
			glm::mat4 projectionMatrix;
		};
		static Matrix_VP* m_Matrix_VP;
	};
}