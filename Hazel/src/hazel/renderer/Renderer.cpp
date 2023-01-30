#include "hzpch.h"
#include "Renderer.h"

namespace Hazel {

	Renderer::Matrix_VP* Renderer::m_Matrix_VP = new Matrix_VP;
	void Renderer::BeginScene(Camera& camera)
	{
		m_Matrix_VP->viewMatrix = camera.GetViewMatrix();
		m_Matrix_VP->projectionMatrix = camera.GetProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadUniformMat4("view", m_Matrix_VP->viewMatrix);
		shader->UploadUniformMat4("projection", m_Matrix_VP->projectionMatrix);

		vertexArray->Bind();
		RenderCommend::DrawIndexed(vertexArray);
	}

}