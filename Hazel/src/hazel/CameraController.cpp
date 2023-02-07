#include "hzpch.h"
#include "CameraController.h"

#include "hazel\Input.h"
#include "hazel\KeyCodes.h"

namespace Hazel {
	/// <summary>
	/// OrthographicCameraController
	/// </summary>
	/// <param name="aspectRatio"></param>
	/// <param name="rotation"></param>
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: 
		m_AspectRatio(aspectRatio),
		m_Camera(-aspectRatio * m_ZoomLevel, aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
		m_Rotation(rotation)
	{

	}

	void OrthographicCameraController::Update(Timestep ts)
	{
		if (m_Lock) return;
		if (Input::IsKeyPressed(HZ_KEY_W))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		if (Input::IsKeyPressed(HZ_KEY_S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		if (Input::IsKeyPressed(HZ_KEY_A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		if (Input::IsKeyPressed(HZ_KEY_D))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(HZ_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Input::IsKeyPressed(HZ_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;
			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		Hazel::EventDispatcher dispather(e);
		dispather.Dispatch<KeyPressedEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnKeyPressed));
		dispather.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispather.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));

	}

	bool OrthographicCameraController::OnMouseMovement(MouseMovedEvent& e)
	{
		return false;
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		if (m_Lock) return false;
		m_ZoomLevel -= e.GetYOffset() * 0.5f;
		m_ZoomLevel = std::max(0.5f, m_ZoomLevel);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnKeyPressed(Hazel::KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == HZ_KEY_LEFT_ALT)
		{
			Lock();
			return false;
		}
		if (e.GetKeyCode() == HZ_KEY_R)
		{
			Reset();
			return false;
		}
		return false;
	}

	/// <summary>
	/// PerspectiveCameraController
	/// </summary>
	/// <param name="aspectRatio"></param>
	PerspectiveCameraController::PerspectiveCameraController(float aspectRatio)
	{
		
	}

	void PerspectiveCameraController::Update(Timestep ts)
	{
	}

	void PerspectiveCameraController::OnEvent(Event& e)
	{
	}

	bool PerspectiveCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		return false;
	}

	bool PerspectiveCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		return false;
	}

	

}