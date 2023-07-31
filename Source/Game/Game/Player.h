#pragma once
#include "Framework/Actor.h"

class Player : public minimum::Actor
{
public:
	Player(float speed, float turnRate, const minimum::Transform transform, const std::shared_ptr<minimum::Model> model) :
		Actor{ transform, model },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{};

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;
};