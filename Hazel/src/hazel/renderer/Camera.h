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
		ROTATE_ANTI
	};

	class Camera
	{
	public:
		Camera() {}
		virtual const glm::vec3& GetPosition() = 0;
		virtual void SetPosition(const glm::vec3& pos) = 0;

		virtual const glm::mat4& GetProjectionMatrix() = 0;
		virtual glm::mat4 GetViewMatrix() = 0;

		virtual void KeyboardInput(Direction direction, float deltaTime) = 0;
		virtual void MouseMovement(float xpos, float ypos) = 0;

		virtual void LockCamera() = 0;
		virtual void UnLockCamera() = 0;

		virtual void ResetCamera() = 0;
	};
	
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float left,float right, float bottom, float top);
	
		inline virtual const glm::vec3& GetPosition() override { return m_CameraPos; }
		inline virtual void SetPosition(const glm::vec3& pos) override { m_CameraPos = pos; }

		inline virtual const glm::mat4& GetProjectionMatrix() override { return m_ProjectionMatrix; }
		inline virtual glm::mat4 GetViewMatrix() override
		{
			m_ViewMatrix = glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);
			return m_ViewMatrix;
		}

		virtual void KeyboardInput(Direction direction, float deltaTime) override ;
		virtual void MouseMovement(float xpos, float ypos) override ;

		inline virtual void LockCamera() { m_Locked = true; }
		inline virtual void UnLockCamera() { m_Locked = false; }

		inline virtual void ResetCamera() 
		{
			m_CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
			m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
			m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		};
	private:
		glm::vec3 m_CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		float m_CameraSpeed = 2.5f;
		float m_CameraRotateSpeed = 2.0f; // degree

	private:
		bool m_FirstMouse = true;
		bool m_Locked = true;
	};

	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float fov, float aspect, float Near, float Far, float FOV_U = 45.0f, float FOV_B = 65.0f);

		inline virtual const glm::vec3& GetPosition() override { return m_CameraPos; }
		inline virtual void SetPosition(const glm::vec3& pos) override { m_CameraPos = pos; }

		inline virtual const glm::mat4& GetProjectionMatrix() override { return m_ProjectionMatrix; }
		inline virtual glm::mat4 GetViewMatrix() override
		{
			m_ViewMatrix = glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);
			return m_ViewMatrix;
		}
		inline virtual void ResetCamera()
		{
			m_CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
			m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
			m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
			m_Yaw = -90.0f;
			m_Pitch = 0.0f;
		};

		virtual void KeyboardInput(Direction direction, float deltaTime) override;
		virtual void MouseMovement(float xpos, float ypos) override;

		inline virtual void LockCamera() { m_Locked = true; }
		inline virtual void UnLockCamera() 
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