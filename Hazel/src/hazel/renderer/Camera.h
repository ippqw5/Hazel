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
			m_Up.x = glm::cos(glm::radians(90.0f + rotation));
			m_Up.y = glm::sin(glm::radians(90.0f + rotation));
		}

		const glm::vec3& GetPosition() { return m_Position; }
		const glm::mat4& GetProjectionMatrix()  { return m_ProjectionMatrix; }
		glm::mat4 GetViewMatrix() 
		{
			m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
			return m_ViewMatrix;
		}
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

	private:
		bool m_FirstMouse = true;
		bool m_Locked = true;
	};

	class PerspectiveCamera
	{
	public:
		PerspectiveCamera() = default;
		PerspectiveCamera(float fov, float aspect, float Near, float Far, float FOV_U = 65.0f, float FOV_B = 45.0f);

		void SetPosition(const glm::vec3& pos) { m_CameraPos = pos; }

		const glm::vec3& GetPosition() { return m_CameraPos; }
		const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
		glm::mat4 GetViewMatrix() 
		{
			m_ViewMatrix = glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);
			return m_ViewMatrix;
		}
		void ResetCamera()
		{
			if (m_Locked) return;
			m_CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
			m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
			m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
			m_Yaw = -90.0f;
			m_Pitch = 0.0f;
		};

		void KeyboardInput(Direction direction, float deltaTime) ;
		void MouseMovement(float xpos, float ypos) ;
		void MouseScroll(float xoffset, float yoffset) ;

		void LockCamera() { m_Locked = true; }
		void UnLockCamera() 
		{ 
			m_Locked = false; 
			m_FirstMouse = true;
		}
	private:
		glm::vec3 m_CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		float m_CameraSpeed = 2.5f;
		float m_CameraRotateSpeed = 2.0f; // degree

	private:
		float m_Fov, m_Fov_U, m_Fov_B;
		float m_Aspect;
		float m_Near, m_Far;
		float m_Yaw, m_Pitch;
		float m_LastX, m_LastY;
	private:
		bool m_FirstMouse = true;
		bool m_Locked = true;
	};
}