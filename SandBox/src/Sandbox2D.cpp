#include "Sandbox2D.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f/720.f, false)
{

}

void Sandbox2D::OnAttach()
{
	m_Texture = Hazel::Texture2D::Create("./assets/Texture/container.jpg",4);
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

	Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Hazel::Renderer2D::DrawQuad({ 0.0f,0.0f }, { 0.5f,0.5f }, m_SquareColor);
	Hazel::Renderer2D::DrawQuad({ 0.5f,0.5f,-0.1f }, { 10.0f,10.0f }, m_Texture, 1);
	Hazel::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Hazel::Event& e)
{
	m_CameraController.OnEvent(e);
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}
