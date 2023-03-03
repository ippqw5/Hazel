#pragma once

#include <Hazel.h>

class Bug
{
	enum class Direction
	{
		Stay = 0,Forward, Back
	};
	using JumpFunction = std::function<float(float)>;
public:
	Bug(const std::string& name = "bug");
	
	void setTexture(const std::string& filepath);
	void setPosition(const glm::vec3& position) { m_Position = position; }
	void setSize(const glm::vec2& size) { m_Size = size; }
	void setJumpFn(float target);

	const glm::vec3& GetPosition() const { return m_Position; }
	const glm::vec2& GetSize() const { return m_Size; }
	const Hazel::Ref<Hazel::Texture2D>& GetTexture() const { return m_Texture; }

	void Update(Hazel::Timestep ts);
	void move(Hazel::Timestep ts);

	void OnEvent(Hazel::Event& e);
private:
	bool OnKeyPressed(Hazel::KeyPressedEvent& e);
	bool OnKeyReleased(Hazel::KeyReleasedEvent& e);
public:
	float m_bugSpeed;
private:
	std::string m_Name;

	glm::vec3 m_Position;
	glm::vec2 m_Size;

	Hazel::Ref<Hazel::Texture2D> m_Texture;
	glm::vec4 m_SquareColor = { 0.0f,0.0f,0.0f,1.0f };

	bool m_Jumping;
	JumpFunction m_JumpFn;
	std::chrono::steady_clock::time_point m_JumpStartTimepoint;
	std::chrono::steady_clock::time_point m_JumpEndTimepoint;
	float m_JumpDuration;
	Direction m_Direction;

};