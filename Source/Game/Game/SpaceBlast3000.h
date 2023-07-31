#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"

class SpaceBlast3000 : public minimum::Game
{
	class Renderer;

public:
	enum class eState 
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		GameOver
	};

public:



	// Inherited via Game
	virtual bool Initialize() override;
	virtual bool Shutdown() override;


	virtual void Update(float dt) override;
	virtual void Draw(minimum::Renderer& renderer) override;

	void SetState(eState state) { m_state = state; }

private:
	eState m_state = eState::Title;
	float m_spawnTimer = 0;
	float m_spawnTime = 1.5f;
	bool enemy3Summoned = false;

	float m_stateTimer = 0;

	std::shared_ptr<minimum::Font> m_font;
	std::unique_ptr<minimum::Text> m_scoreText;
	std::unique_ptr<minimum::Text> m_titleText;
	std::unique_ptr<minimum::Text> m_gameOverText;

};