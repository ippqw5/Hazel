#pragma once

#include <Hazel.h>
#include <imgui/imgui.h>

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

	Hazel::Ref<Hazel::Texture2D> m_Texture;

	glm::vec4 m_SquareColor = { 0.0f,0.0f,0.0f,1.0f };
	
};