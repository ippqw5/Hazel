#include "Bug.h"


Bug::Bug(const std::string& name)
	: m_Name(name), m_Position{0.0f,0.0f,0.0f}, m_Size{0.5f,0.5f}
{
	m_JumpFn = [](float x) { return 0.0f; };
	m_bugSpeed = 1.0f;
	m_Direction = Direction::Stay;
	m_JumpDuration = 0.0f;
	m_Jumping = false;
}

void Bug::setTexture(const std::string& filepath)
{
	m_Texture = Hazel::Texture2D::Create(filepath,4);
}

void Bug::setJumpFn(float target)
{
	float source = m_Position.x;
	m_JumpFn = [source,target](float x) { return 2.0f * (x-source) * (target-x); };
}

void Bug::Update(Hazel::Timestep ts)
{
	/*if (Hazel::Input::IsKeyPressed(HZ_KEY_A) || Hazel::Input::IsKeyPressed(HZ_KEY_LEFT))
		move(ts, Bug::Direction::Back);
	else if (Hazel::Input::IsKeyPressed(HZ_KEY_D) || Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT))
		move(ts, Bug::Direction::Forward);*/
	if (m_Jumping) move(ts);

}

void Bug::move(Hazel::Timestep ts)
{
	float delt = ts.GetSeconds();
	switch (m_Direction)
	{
	case Bug::Direction::Stay:
		break;
	case Bug::Direction::Forward:
		if (delt > m_JumpDuration)
		{
			delt = m_JumpDuration;
			m_Direction = Direction::Stay;
			m_Jumping = false;
		}
		else {
			m_JumpDuration = (m_JumpDuration - delt) >= 0.0f ? (m_JumpDuration - delt) : 0.0f;
		}
		m_Position.x += m_bugSpeed * delt;
		m_Position.y = m_JumpFn(m_Position.x);
		break;
	case Bug::Direction::Back:
		if (delt > m_JumpDuration)
		{
			delt = m_JumpDuration;
			m_Direction = Direction::Stay;
			m_Jumping = false;
		}
		else {
			m_JumpDuration = (m_JumpDuration - delt) >= 0.0f ? (m_JumpDuration - delt) : 0.0f;
		}
		m_Position.x -= m_bugSpeed * delt;
		m_Position.y = m_JumpFn(m_Position.x);
		break;
	default:
		break;
	}
}

void Bug::OnEvent(Hazel::Event& e)
{
	Hazel::EventDispatcher dispather(e);
	dispather.Dispatch<Hazel::KeyPressedEvent>(HZ_BIND_EVENT_FN(Bug::OnKeyPressed));
	dispather.Dispatch<Hazel::KeyReleasedEvent>(HZ_BIND_EVENT_FN(Bug::OnKeyReleased));


}

bool Bug::OnKeyPressed(Hazel::KeyPressedEvent& e)
{
	if (m_Direction != Direction::Stay) return false;
	if (e.GetKeyCode() == HZ_KEY_D)
	{
		if (e.IsRepeat()) return false;
		m_Direction = Direction::Forward;
		m_JumpStartTimepoint = std::chrono::high_resolution_clock::now();
	}
	else if (e.GetKeyCode() == HZ_KEY_A)
	{
		if (e.IsRepeat()) return false;
		m_Direction = Direction::Back;
	}
	return false;
}

bool Bug::OnKeyReleased(Hazel::KeyReleasedEvent& e)
{
	if (e.GetKeyCode() == HZ_KEY_D && m_Direction == Direction::Forward)
	{
		m_JumpEndTimepoint = std::chrono::high_resolution_clock::now();
		auto jumpduration = std::chrono::duration_cast<std::chrono::milliseconds>(m_JumpEndTimepoint - m_JumpStartTimepoint).count();
		m_JumpDuration = (float)jumpduration * 0.001f;
		setJumpFn(m_Position.x + m_JumpDuration * m_bugSpeed);
		m_Jumping = true;
	}
	else if (e.GetKeyCode() == HZ_KEY_A && m_Direction == Direction::Back) {
		m_JumpDuration = 0.5f;
		setJumpFn(m_Position.x - m_JumpDuration * m_bugSpeed);
		m_Jumping = true;
	}
	return false;
}
