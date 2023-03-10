#pragma once
#include "hazel\Core\Core.h"
#include "hazel\events/Event.h"
#include "hazel\Core\Timestep.h"

namespace Hazel {
	class HAZEL_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnEvent(Event& e) {}
		virtual void OnImGuiRender() {}
		
		inline const std::string& Getname() const { return m_Name; }
	private:
		std::string m_Name;
	};
}