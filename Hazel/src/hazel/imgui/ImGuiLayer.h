#pragma once

#include "hazel\Core.h"
#include "hazel\Layer.h"
#include "hazel\events\MouseEvent.h"
#include "hazel\events\AppEvent.h"
#include "hazel\events\KeyEvent.h"
namespace Hazel {
	class HAZEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}