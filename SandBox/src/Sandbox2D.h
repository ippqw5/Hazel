#pragma once

#include <Hazel.h>
#include <imgui.h>

class Sandbox2D : public Hazel::Layer
{
public:
	Sandbox2D();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Hazel::Timestep ts) override;

	void OnEvent(Hazel::Event& e) override;

	void OnImGuiRender() override;
private:
	Hazel::OrthographicCameraController m_CameraController;

	Hazel::Ref<Hazel::VertexBuffer> m_VertexBuffer;
	Hazel::Ref<Hazel::IndexBuffer> m_IndexBuffer;
	Hazel::Ref<Hazel::VertexArray> m_VertexArray;

	Hazel::Ref<Hazel::Shader> m_Shader;

	glm::vec3 m_SquareColor = { 0.0f,0.0f,0.0f };
};