#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Hazel {

	enum class Direction {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		ROTATE,
		ROTATE_ANTI,
		UP,
		DOWN
	};
	
	class OrthographicCamera
	{
	public:
		OrthographicCamera() = default;
		OrthographicCamera(float left,float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);
		void SetPosition(const glm::vec3& pos) { m_Position = pos; }
		void SetRotation(float rotation) // rotate by (0,0,1)
		{ 
			m_Up.x = glm::cos(glm::radians(rotation));
			m_Up.y = glm::sin(glm::radians(rotation));
		}

		const glm::vec3& GetPosition() { return m_Position; }
		const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() 
		{
			m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
			return m_ViewMatrix;
		}

	public:
		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

	};

	class PerspectiveCamera
	{
	public:
		PerspectiveCamera() = default;
		PerspectiveCamera(float fov, float aspect, float Near, float Far, float FOV_B = 45.0f, float FOV_U = 120.0f);

		void SetProjection(float fov, float aspect, float Near, float Far);
		void SetPosition(const glm::vec3& pos) { m_Position = pos; }
		void SetRotation(float rotation) { }
		void ReCalculate() 
		{
			m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_Aspect, m_Near, m_Far);
			m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
		}

		inline const glm::vec3& GetPosition() { return m_Position; }
		inline const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewMatrix() 
		{
			m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
			return m_ViewMatrix;
		}

	public:
		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
		float m_Fov, m_Fov_U, m_Fov_B;
		float m_Aspect;
		float m_Near, m_Far;
		float m_Yaw, m_Pitch;
		float m_LastX, m_LastY;

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

	};
}