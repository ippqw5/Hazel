#include "BugBattle.h"

BugBattle::BugBattle()
	: Layer("BugBattle"), m_CameraController(1280.0f / 720.f, false)
{
	m_player = Bug("player");
	m_bot = Bug("bug");
}

void BugBattle::OnAttach()
{
	m_Background = Hazel::Texture2D::Create("./assets/Texture/windows.jpg",4);
	m_player.setTexture("./assets/Texture/siu.jpg");
	m_player.setPosition({ -0.5f,0.0f,-0.1f });
	m_bot.setTexture("./assets/Texture/ikun.jpg");
	m_bot.setPosition({ 0.5f,0.0f,-0.1f });
}

void BugBattle::OnDetach()
{
}

void BugBattle::OnUpdate(Hazel::Timestep ts)
{
	m_player.Update(ts);
	Hazel::RenderCommend::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
	Hazel::RenderCommend::Clear();

	Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Hazel::Renderer2D::DrawQuad({ 0.0f,0.0f,-0.5f }, { 4.0f,2.0f }, m_Background);
	Hazel::Renderer2D::DrawQuad(m_player.GetPosition(), m_player.GetSize(), m_player.GetTexture());
	Hazel::Renderer2D::DrawQuad(m_bot.GetPosition(), m_bot.GetSize(), m_bot.GetTexture());
	Hazel::Renderer2D::EndScene();
}

void BugBattle::OnEvent(Hazel::Event& e)
{
	m_player.OnEvent(e);
}

void BugBattle::OnImGuiRender()
{
	ImGui::Begin("Player Size Setting");
	static float size[2] = {0.5f, 0.5f};
	ImGui::SliderFloat2("Size", size, 0.2f, 2.0f);
	ImGui::SliderFloat("Speed", &m_player.m_bugSpeed, 0.5f, 5.0f);
	m_player.setSize({ size[0],size[1] });
	ImGui::End();
}
