#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"

#include "Framework/Event.h"
#include "Framework/EventManager.h"

class JumpDingus3 : public minimum::Game, public minimum::IEventListener
{
public:
	enum eState
	{
		Title,
		StartGame,
		StartLevel,
		Tutorial,
		Game,
		PlayerDeadStart,
		PlayerDead,
		GameOverStart,
		GameOver,
		Win
	};

public:
	virtual bool Initialize() override;
	virtual bool Shutdown() override;

	virtual void Update(float dt) override;
	virtual void Draw(minimum::Renderer& renderer) override;

	void SetState(eState state) { m_state = state; }

	virtual void OnAddPoints(const minimum::Event& event);
	void OnPlayerDead(const minimum::Event& event);

private:
	eState m_state = eState::Title;
	float m_spawnTimer = 0;
	float m_spawnTime = 2.5f;

	float m_powerTimer = 0;
	float m_powerTime = 8.0f;
};