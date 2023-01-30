#include "hzpch.h"
#include "Camera.h"

namespace Hazel {
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
	{
	}

	PerspectiveCamera::PerspectiveCamera(float Fov, float Aspect, float Near, float Far, float FOV_U, float FOV_B)
		: m_Fov(Fov), m_Fov_U(FOV_U), m_Fov_B(FOV_B), m_Aspect(Aspect), m_Near(Near), m_Far(Far),
		m_Yaw(-90.0f), m_Pitch(0.0f), m_LastX(0.0f), m_LastY(0.0f)
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(Fov), Aspect, Near, Far);
	}

	void PerspectiveCamera::KeyboardInput(Direction direction)
	{
		if (m_Locked == true) return;
		if (direction == Direction::FORWARD)
			m_CameraPos += m_CameraSpeed * m_CameraFront;
		if (direction == Direction::BACKWARD)
			m_CameraPos -= m_CameraSpeed * m_CameraFront;
		if (direction == Direction::LEFT)
			m_CameraPos -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * m_CameraSpeed;
		if (direction == Direction::RIGHT)
			m_CameraPos += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * m_CameraSpeed;
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

		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;

		glm::vec3 front(0.0f);
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_CameraFront = glm::normalize(front);
	}


}