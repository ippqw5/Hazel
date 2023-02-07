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

		void Lock() 
		{
			m_Lock = (!m_Lock);
		}
		void Reset() {};

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

		glm::vec3 m_CameraPosition = { 0.0f,0.0f,0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 2.5f;
		float m_CameraRotationSpeed = 20.0f; // degree
	};


	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController(float aspectRatio);

		void Update(Timestep ts);
		void OnEvent(Event& e);

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;

		PerspectiveCamera m_Camera;
		glm::vec3 m_CameraPosition = { 0.0f,0.0f,0.0f };
		float m_CameraTranslateSpeed = 2.5f;
		float m_CameraRotateSpeed = 0.5f; // degree
	};
}