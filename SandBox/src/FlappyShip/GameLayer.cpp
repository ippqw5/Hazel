#include "GameLayer.h"
using namespace Hazel;
GameLayer::GameLayer()
	: Layer("GameLayer")
{
	auto& window = Application::Get().GetWindow();
	CreateCamera(window.GetWidth(), window.GetHeight());

	Random::Init();
}

void GameLayer::OnAttach()
{
	m_Level.Init();
	ImGuiIO io = ImGui::GetIO();
	defaultFont = io.Fonts->AddFontDefault();
	//m_Font = defaultFont;
	m_Font = io.Fonts->AddFontFromFileTTF("./assets/OpenSans-Regular.ttf", 120.0f);
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate(Hazel::Timestep ts)
{
	m_Time += ts;
	if ((int)(m_Time * 10.0f) % 8 > 4)
		m_Blink = !m_Blink;
	if (m_Level.IsGameOver())
		m_State = GameState::GameOver;

	const auto& playerPos = m_Level.GetPlayer().GetPosition();
	m_Camera->SetPosition({ playerPos.x, playerPos.y, 0.0f });

	switch (m_State)
	{
	case GameState::Play:
	{
		m_Level.OnUpdate(ts);
		break;
	}
	}

	RenderCommend::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
	RenderCommend::Clear();

	Renderer2D::BeginScene(*m_Camera);
	m_Level.OnRender();
	Renderer2D::EndScene();
}

void GameLayer::OnEvent(Hazel::Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(GameLayer::OnWindowResize));
	dispatcher.Dispatch<MouseButtonPressedEvent>(HZ_BIND_EVENT_FN(GameLayer::OnMouseButtonPressed));
}

void GameLayer::OnImGuiRender()
{
	
	ImGui::Begin("Settings");
	m_Level.OnImGuiRender();
	ImGui::End();

	switch (m_State)
	{
	case GameState::Play:
	{
		uint32_t playerScore = m_Level.GetPlayer().GetScore();
		std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
		ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, ImGui::GetWindowPos(), 0xffffffff, scoreStr.c_str());
		break;
	}
	case GameState::MainMenu:
	{
		auto pos = ImGui::GetWindowPos();
		auto width = Application::Get().GetWindow().GetWidth();
		auto height = Application::Get().GetWindow().GetHeight();
		pos.x += width * 0.5f - 300.0f;
		pos.y += 50.0f;
		//if (m_Blink)
		ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");
		pos.y -= 50.f;
		ImGui::GetForegroundDrawList()->AddText(m_Font, 60.0f, pos, 0xffffffff, "Press [space] to control!");
		break;
	}
	case GameState::GameOver:
	{
		auto pos = ImGui::GetWindowPos();
		auto width = Application::Get().GetWindow().GetWidth();
		auto height = Application::Get().GetWindow().GetHeight();
		pos.x += width * 0.5f - 300.0f;
		pos.y += 50.0f;
		//if (m_Blink)
			ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");

		pos.x += 200.0f;
		pos.y += 150.0f;
		uint32_t playerScore = m_Level.GetPlayer().GetScore();
		std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
		ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, pos, 0xffffffff, scoreStr.c_str());
		break;
	}
	}
}

bool GameLayer::OnMouseButtonPressed(Hazel::MouseButtonPressedEvent& e)
{
	if (m_State == GameState::GameOver)
		m_Level.Reset();

	m_State = GameState::Play;
	return false;
}

bool GameLayer::OnWindowResize(Hazel::WindowResizeEvent& e)
{
	CreateCamera(e.GetWidth(), e.GetHeight());
	return false;
}

void GameLayer::CreateCamera(uint32_t width, uint32_t height)
{
	float aspectRatio = (float)width / (float)height;

	float camWidth = 8.0f;
	float bottom = -camWidth;
	float top = camWidth;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;
	m_Camera = CreateScope<OrthographicCamera>(left, right, bottom, top);
}
