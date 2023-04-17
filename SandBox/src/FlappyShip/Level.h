#pragma once
#include "Player.h"
#include "Color.h"
#include "Random.h"

struct Pillar
{
	glm::vec3 TopPosition = { 0.0f, 10.0f, 0.0f };
	glm::vec2 TopScale = { 15.0f, 20.0f };

	glm::vec3 BottomPosition = { 10.0f, -10.0f, 0.0f };
	glm::vec2 BottomScale = { 15.0f, 20.0f };
};

class Level
{
public:
	void Init();
	
	void OnUpdate(Hazel::Timestep ts);
	void OnRender();
	void OnImGuiRender();

	Player& GetPlayer() { return m_Player; }
	void Reset();
	bool IsGameOver() { return m_GameOver; }
private:
	void CreatePillar(int index, float offset);
	bool CollisionTest();
	void GameOver();
private:
	Player m_Player;
	Hazel::Ref<Hazel::Texture2D> m_TriangleTexture;

	bool m_GameOver = false;

	float m_PillarTarget = 30.0f;
	int m_PillarIndex = 0;
	std::vector<Pillar> m_Pillars;
	glm::vec3 m_PillarHSV = { 0.0f, 0.8f, 0.8f };

};