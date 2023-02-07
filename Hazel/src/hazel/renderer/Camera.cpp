#include "hzpch.h"
#include "Camera.h"

namespace Hazel {

	// --------------------------------------------------
	// Orthographic Camera ------------------------------
	// --------------------------------------------------
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
	{
		m_ViewMatrix = glm::mat4(1.0f);
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	}
	// --------------------------------------------------
	// Persepective Camera ------------------------------
	// --------------------------------------------------
	PerspectiveCamera::PerspectiveCamera(float Fov, float Aspect, float Near, float Far, float FOV_B, float FOV_U)
		: m_Fov(Fov), m_Fov_B(FOV_B), m_Fov_U(FOV_U), m_Aspect(Aspect), m_Near(Near), m_Far(Far),
		m_Yaw(-90.0f), m_Pitch(0.0f), m_LastX(0.0f), m_LastY(0.0f)
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(Fov), Aspect, Near, Far);
		m_ViewMatrix = glm::mat4(1.0f);
	}

	void PerspectiveCamera::SetProjection(float fov, float aspect, float Near, float Far)
	{
		m_Aspect = aspect;
		m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspect, Near, Far);
	}


	/*void PerspectiveCamera::KeyboardInput(Direction direction,float deltaTime)
	{
		if (m_Locked == true) return;
		switch (direction)
		{
		case Hazel::Direction::FORWARD:
			m_CameraPos += deltaTime * m_CameraSpeed * m_CameraFront;
			break;
		case Hazel::Direction::BACKWARD:
			m_CameraPos -= deltaTime * m_CameraSpeed * m_CameraFront;
			break;
		case Hazel::Direction::LEFT:
			m_CameraPos -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * deltaTime * m_CameraSpeed;
			break;
		case Hazel::Direction::RIGHT:
			m_CameraPos += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * deltaTime * m_CameraSpeed;
			break;
		case Hazel::Direction::ROTATE:
			m_CameraUp = glm::rotate(glm::mat4(1.0f), glm::radians(m_CameraRotateSpeed * deltaTime), m_CameraFront)
				* glm::vec4(m_CameraUp, 1.0f);
			break;
		case Hazel::Direction::ROTATE_ANTI:
			m_CameraUp = glm::rotate(glm::mat4(1.0f), glm::radians(-m_CameraRotateSpeed * deltaTime), m_CameraFront)
				* glm::vec4(m_CameraUp, 1.0f);
			break;
		case Hazel::Direction::UP :
			m_CameraPos += deltaTime * m_CameraSpeed * m_CameraUp;
			break;
		case Hazel::Direction::DOWN :
			m_CameraPos -= deltaTime * m_CameraSpeed * m_CameraUp;
			break;
		default:
			break;
		}
	}

	void PerspectiveCamera::MouseScroll(float xoffset, float yoffset)
	{
		/*if (m_Locked == true) return;
		float temp = m_Fov - yoffset;
		if (m_Fov_B <= temp && temp <= m_Fov_U)	m_Fov = temp;
		else if (m_Fov_B > temp)				m_Fov = m_Fov_B;
		else									m_Fov = m_Fov_U;

		m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_Aspect, m_Near, m_Far);
	}
	*/
}