#pragma once

#include <Hazel.h>
#include <imgui/imgui.h>

#include "Level.h"

class GameLayer : public Hazel::Layer
{
public:
	GameLayer();
	
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Hazel::Timestep ts) override;

	void OnEvent(Hazel::Event& e) override;

	void OnImGuiRender() override;

	bool OnMouseButtonPressed(Hazel::MouseButtonPressedEvent& e);
	bool OnWindowResize(Hazel::WindowResizeEvent& e);
private:
	void CreateCamera(uint32_t width, uint32_t height);
private:
	Hazel::Scope<Hazel::OrthographicCamera> m_Camera;
	Level m_Level;

	ImFont* m_Font, *defaultFont;
	float m_Time = 0.0f;
	bool m_Blink = false;

	enum class GameState
	{
		Play = 0, MainMenu = 1, GameOver = 2
	};

	GameState m_State = GameState::MainMenu;
};