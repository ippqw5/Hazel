#include "Sandbox2D.h"
#include <chrono>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f/720.f, false)
{

}

void Sandbox2D::OnAttach()
{
	m_Texture = Hazel::Texture2D::Create("./assets/Texture/Checkerboard.png",4);
}

void Sandbox2D::OnDetach()
{ 
}

void Sandbox2D::OnUpdate(Hazel::Timestep ts)
{
	HZ_PROFILE_FUNCTION();
	// Update
	m_CameraController.Update(ts);

	{
		HZ_PROFILE_SCOPE("Sandbox2D - Render SetClear")
		// Render
		Hazel::RenderCommend::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		Hazel::RenderCommend::Clear();
	}

	{
		HZ_PROFILE_SCOPE("Sandbox2D - Render Draw ");
		Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 0.5f, 0.5f }, 0.0f, m_SquareColor);
		Hazel::Renderer2D::DrawRotatedQuad({ 1.0f, 2.0f, 0.0f }, { 0.5f, 0.5f }, glm::radians(45.0f), 0.0f, {0.2f, 0.5f, 0.3f, 1.0f});
		Hazel::Renderer2D::DrawQuad({ 0.5f, 0.5f,-0.1f }, { 5.0f,5.0f }, m_Texture, 10.0f, 0.0f);
		Hazel::Renderer2D::EndScene();
	}
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

	static bool my_tool_active = true;
	if (my_tool_active)
	{
		// Create a window called "My First Tool", with a menu bar.
		ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
				if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
				if (ImGui::MenuItem("Close", "Ctrl+W")) { my_tool_active = false; }
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		static float my_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		// Edit a color stored as 4 floats
		ImGui::ColorEdit4("Color", my_color);

		// Generate samples and plot them
		float samples[100];
		for (int n = 0; n < 100; n++)
			samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
		ImGui::PlotLines("Samples", samples, 100);

		// Display contents in a scrolling region
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
		ImGui::BeginChild("Scrolling");
		for (int n = 0; n < 50; n++)
			ImGui::Text("%04d: Some text", n);		
		ImGui::EndChild();
		ImGui::End();

		
	}
}
