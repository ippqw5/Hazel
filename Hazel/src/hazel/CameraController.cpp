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
		: m_Camera(-aspectRatio * m_ZoomLevel, aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
		m_Rotation(rotation)
	{

	}

	void OrthographicCameraController::Update(Timestep ts)
	{
		if (Input::IsKeyPressed(HZ_KEY_W))
			m_Camera.KeyboardInput(Direction::FORWARD, ts);
		if (Input::IsKeyPressed(HZ_KEY_S))
			m_Camera.KeyboardInput(Direction::BACKWARD, ts);
		if (Input::IsKeyPressed(HZ_KEY_A))
			m_Camera.KeyboardInput(Direction::LEFT, ts);
		if (Input::IsKeyPressed(HZ_KEY_D))
			m_Camera.KeyboardInput(Direction::RIGHT, ts);
		if (m_Rotation)
		{
			if (Input::IsKeyPressed(HZ_KEY_Q))
				m_Camera.KeyboardInput(Direction::ROTATE, ts);
			if (Input::IsKeyPressed(HZ_KEY_E))
				m_Camera.KeyboardInput(Direction::ROTATE_ANTI, ts);
		}
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		Hazel::EventDispatcher dispather(e);
		dispather.Dispatch<Hazel::MouseScrolledEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispather.Dispatch<Hazel::WindowResizeEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));

	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_Camera.MouseScroll(e.GetXOffset(), e.GetYOffset());
		return true;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
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