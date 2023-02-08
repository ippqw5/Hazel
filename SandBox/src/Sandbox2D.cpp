#include "Sandbox2D.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f/720.f, false)
{

}

void Sandbox2D::OnAttach()
{
	float vertices[] = {
		//      |     --Pos--     |   
				-0.5f, -0.5f, 0.0f,
				 0.5f, -0.5f, 0.0f,
				 0.5f,  0.5f, 0.0f,
				-0.5f,  0.5f, 0.0f,
	};

	m_VertexBuffer = Hazel::VertexBuffer::Create(vertices, sizeof(vertices));
	Hazel::BufferLayout layout = {
		{ Hazel::ShaderDataType::Float3, "a_Position" },
	};
	m_VertexBuffer->SetLayout(layout);

	unsigned int indices[] = { 0,1,2,2,3,0 };
	m_IndexBuffer = Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));

	m_VertexArray = Hazel::VertexArray::Create();
	m_VertexArray->AddVertexBuffer(m_VertexBuffer);
	m_VertexArray->SetIndexBuffer(m_IndexBuffer);
	m_VertexArray->UnBind();

	HZ_ASSERT(Hazel::ShaderLibrary::IsInit(), "ShaderLibrary not initialized!");

	m_Shader = Hazel::ShaderLibrary::GetShader("FlatColorShader");

}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Hazel::Timestep ts)
{
	// Update
	m_CameraController.Update(ts);

	// Render
	Hazel::RenderCommend::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
	Hazel::RenderCommend::Clear();

	Hazel::Renderer::BeginScene(m_CameraController.GetCamera());

	m_Shader->Bind();
	m_Shader->UploadUniformf3("u_Color", m_SquareColor);

	Hazel::Renderer::Submit(m_Shader, m_VertexArray);
}

void Sandbox2D::OnEvent(Hazel::Event& e)
{
	m_CameraController.OnEvent(e);
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}
