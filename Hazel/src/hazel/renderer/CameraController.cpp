#include "hzpch.h"
#include "CameraController.h"

#include "hazel\Core\Application.h"
#include "hazel\Core\Input.h"
#include "hazel\Core\KeyCodes.h"

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
			m_Camera.m_Position += ts * m_CameraTranslationSpeed * m_Camera.m_Up;
		if (Input::IsKeyPressed(HZ_KEY_S))
			m_Camera.m_Position -= ts * m_CameraTranslationSpeed * m_Camera.m_Up;
		if (Input::IsKeyPressed(HZ_KEY_A))
			m_Camera.m_Position -= ts * m_CameraTranslationSpeed * glm::normalize(glm::cross(m_Camera.m_Front, m_Camera.m_Up)) ;
		if (Input::IsKeyPressed(HZ_KEY_D))
			m_Camera.m_Position += ts * m_CameraTranslationSpeed * glm::normalize(glm::cross(m_Camera.m_Front, m_Camera.m_Up)) ;

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(HZ_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Input::IsKeyPressed(HZ_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;
			m_Camera.SetRotation(m_CameraRotation + 90.0f);
		}

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
			LockSwitch();
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
	PerspectiveCameraController::PerspectiveCameraController(float aspectRatio, float fov, float Near, float Far, bool rotation)
		: m_AspectRatio(aspectRatio), m_Rotation(rotation),
		m_Camera(fov, aspectRatio, Near, Far)
	{
		
	}

	void PerspectiveCameraController::Update(Timestep ts)
	{
		if (m_Lock) return;
		if (Input::IsKeyPressed(HZ_KEY_W))
			m_Camera.m_Position += ts * m_CameraTranslationSpeed * m_Camera.m_Front;
		if (Input::IsKeyPressed(HZ_KEY_S))
			m_Camera.m_Position -= ts * m_CameraTranslationSpeed * m_Camera.m_Front;
		if (Input::IsKeyPressed(HZ_KEY_A))
			m_Camera.m_Position -= ts * m_CameraTranslationSpeed * glm::normalize(glm::cross(m_Camera.m_Front, m_Camera.m_Up));
		if (Input::IsKeyPressed(HZ_KEY_D))
			m_Camera.m_Position += ts * m_CameraTranslationSpeed * glm::normalize(glm::cross(m_Camera.m_Front, m_Camera.m_Up));
		if (Input::IsKeyPressed(HZ_KEY_UP))
			m_Camera.m_Position += ts * m_CameraTranslationSpeed * m_Camera.m_Up;
		if (Input::IsKeyPressed(HZ_KEY_DOWN))
			m_Camera.m_Position -= ts * m_CameraTranslationSpeed * m_Camera.m_Up;

		if (m_Rotation)
		{

		}

	}

	void PerspectiveCameraController::OnEvent(Event& e)
	{
		Hazel::EventDispatcher dispather(e);
		dispather.Dispatch<KeyPressedEvent>(HZ_BIND_EVENT_FN(PerspectiveCameraController::OnKeyPressed));
		dispather.Dispatch<MouseMovedEvent>(HZ_BIND_EVENT_FN(PerspectiveCameraController::OnMouseMovement));
		dispather.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(PerspectiveCameraController::OnWindowResized));
		dispather.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(PerspectiveCameraController::OnMouseScrolled));
	}


	bool PerspectiveCameraController::OnMouseMovement(MouseMovedEvent& e)
	{
		float xpos = e.GetX(), ypos = e.GetY();
		if (m_Lock == true) return false;
		if (m_FirstMouse == true)
		{
			m_FirstMouse = false;
			m_Camera.m_LastX = xpos;
			m_Camera.m_LastY = ypos;
		}
		float xoffset = xpos - m_Camera.m_LastX;
		float yoffset = m_Camera.m_LastY - ypos;

		m_Camera.m_LastX = xpos;
		m_Camera.m_LastY = ypos;

		float sensitivity = 0.05f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		m_Camera.m_Yaw += xoffset;
		m_Camera.m_Pitch += yoffset;

		if (m_Camera.m_Pitch > 360.0f)
			m_Camera.m_Pitch -= 360.f;
		if (m_Camera.m_Pitch < -360.f)
			m_Camera.m_Pitch += 360.f;

		glm::vec3 front(0.0f);
		front.x = cos(glm::radians(m_Camera.m_Yaw)) * cos(glm::radians(m_Camera.m_Pitch));
		front.y = sin(glm::radians(m_Camera.m_Pitch));
		front.z = sin(glm::radians(m_Camera.m_Yaw)) * cos(glm::radians(m_Camera.m_Pitch));
		m_Camera.m_Front = glm::normalize(front);
		return false;
	}

	bool PerspectiveCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		if (m_Lock) return false;
		m_ZoomLevel -= e.GetYOffset() * 0.5f;
		m_ZoomLevel = std::max(0.5f, m_ZoomLevel);

		float temp = m_Camera.m_Fov * m_ZoomLevel;
		if (m_Camera.m_Fov_B <= temp && temp <= m_Camera.m_Fov_U)	
			m_Camera.m_Fov = temp;
		else if (m_Camera.m_Fov_B > temp)				
			m_Camera.m_Fov = m_Camera.m_Fov_B;
		else									
			m_Camera.m_Fov = m_Camera.m_Fov_U;

		m_Camera.SetProjection(m_Camera.m_Fov, m_Camera.m_Aspect, m_Camera.m_Near, m_Camera.m_Far);
		return false;
	}

	bool PerspectiveCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(m_Camera.m_Fov, m_AspectRatio, m_Camera.m_Near, m_Camera.m_Far);
		return false;
	}

	bool PerspectiveCameraController::OnKeyPressed(KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == HZ_KEY_LEFT_ALT)
		{
			Hazel::Application::Get().GetWindow().LockSwitch();
			LockSwitch();
			return false;
		}
		if (e.GetKeyCode() == HZ_KEY_R)
		{
			Reset();
			return false;
		}
		return false;
	}

}