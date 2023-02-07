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
	PerspectiveCamera::PerspectiveCamera(float Fov, float Aspect, float Near, float Far, float FOV_U, float FOV_B)
		: m_Fov(Fov), m_Fov_U(FOV_U), m_Fov_B(FOV_B), m_Aspect(Aspect), m_Near(Near), m_Far(Far),
		m_Yaw(-90.0f), m_Pitch(0.0f), m_LastX(0.0f), m_LastY(0.0f)
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(Fov), Aspect, Near, Far);
		m_ViewMatrix = glm::mat4(1.0f);
	}

	void PerspectiveCamera::KeyboardInput(Direction direction,float deltaTime)
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
			m_CameraUp = glm::rotate(glm::mat4(1.0f), glm::radians(m_CameraRotateSpeed), deltaTime * m_CameraFront)
				* glm::vec4(m_CameraUp, 1.0f);
			break;
		case Hazel::Direction::ROTATE_ANTI:
			m_CameraUp = glm::rotate(glm::mat4(1.0f), glm::radians(-m_CameraRotateSpeed), deltaTime * m_CameraFront)
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

	void PerspectiveCamera::MouseMovement(float xpos, float ypos)
	{
		if (m_Locked == true) return;
		if (m_FirstMouse == true)
		{
			m_FirstMouse = false;
			m_LastX = xpos;
			m_LastY = ypos;
		}
		float xoffset = xpos - m_LastX;
		float yoffset = m_LastY - ypos;

		m_LastX = xpos;
		m_LastY = ypos;

		float sensitivity = 0.05f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		m_Yaw += xoffset;
		m_Pitch += yoffset;

		if (m_Pitch > 360.0f)
			m_Pitch -= 360.f;
		if (m_Pitch < -360.f)
			m_Pitch += 360.f;

		glm::vec3 front(0.0f);
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_CameraFront = glm::normalize(front);
	}

	void PerspectiveCamera::MouseScroll(float xoffset, float yoffset)
	{
		if (m_Locked == true) return;
		float temp = m_Fov - yoffset;
		if (m_Fov_B <= temp && temp <= m_Fov_U)	m_Fov = temp;
		else if (m_Fov_B > temp)				m_Fov = m_Fov_B;
		else									m_Fov = m_Fov_U;

		m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_Aspect, m_Near, m_Far);
	}

}