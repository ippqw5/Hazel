#pragma once
#include "hazel\renderer\Camera.h"
#include "hazel\Core\Timestep.h"

#include "hazel\events\AppEvent.h"
#include "hazel\events\KeyEvent.h"
#include "hazel\events\MouseEvent.h"

namespace Hazel {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController() = default;
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void Update(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		void LockSwitch() 
		{
			m_Lock = (!m_Lock);
		}
		void Reset() 
		{
			m_Camera.m_Position = { 0.0f, 0.0f, 0.0f };
			m_Camera.m_Front = { 0.0f, 0.0f, -1.0f };
			m_Camera.m_Up = { 0.0f, 1.0f, 0.0f };
			m_CameraRotation = 0.0f;
		}
	private:
		bool OnMouseMovement(MouseMovedEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		bool  m_Rotation;
		bool  m_Lock = false;

		OrthographicCamera m_Camera;

		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 2.5f;
		float m_CameraRotationSpeed = 20.0f; // degree
	};


	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController(float aspectRatio, float fov, float Near, float Far, bool rotation = false);

		void Update(Timestep ts);
		void OnEvent(Event& e);

		PerspectiveCamera& GetCamera() { return m_Camera; }
		const PerspectiveCamera& GetCamera() const { return m_Camera; }

		void LockSwitch()
		{
			m_Lock = (!m_Lock);
			m_FirstMouse = true;
		}
		void Reset()
		{
			if (m_Lock) return;
			m_ZoomLevel = 1.0f;

			m_Camera.m_Position = { 0.0f, 0.0f, 3.0f };
			m_Camera.m_Front = { 0.0f, 0.0f, -1.0f };
			m_Camera.m_Up = { 0.0f, 1.0f, 0.0f };
			m_Camera.m_Fov = 60.0f;
			m_Camera.m_Yaw = -90.0f;
			m_Camera.m_Pitch = 0.0f;
			m_Camera.ReCalculate();
		}
	private:
		bool OnMouseMovement(MouseMovedEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;

		bool  m_Rotation;
		bool  m_Lock = true;
		bool  m_FirstMouse = true;

		PerspectiveCamera m_Camera;

		float m_CameraTranslationSpeed = 2.5f;
		float m_CameraRotationSpeed = 20.0f; // degree
	};
}