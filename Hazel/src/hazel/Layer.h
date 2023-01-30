#pragma once
#include "Core.h"
#include "events/Event.h"

namespace Hazel {
	class HAZEL_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& e) {}
		virtual void OnImGuiRender() {}
		
		inline const std::string& Getname() const { return m_Name; }
	private:
		std::string m_Name;
	};
}