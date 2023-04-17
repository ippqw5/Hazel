#pragma once
#include <Hazel.h>
#include <imgui/imgui.h>

#include "Bug.h"

class BugBattle : public Hazel::Layer
{
public:
	BugBattle();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Hazel::Timestep ts) override;

	void OnEvent(Hazel::Event& e) override;

	void OnImGuiRender() override;
private:
	Hazel::OrthographicCameraController m_CameraController;
	Hazel::Ref<Hazel::Texture2D> m_Background;
	Bug m_player, m_bot;
};