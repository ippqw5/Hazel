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

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		bool  m_Rotation;

		OrthographicCamera m_Camera; 
	};


	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController() = default;
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

	};
}