#pragma once
#include "Framework/Actor.h"

class Weapon : public minimum::Actor
{
public:

	Weapon(float speed, const minimum::Transform& transform) :
		Actor{ transform },
		m_speed{ speed }
	{
		lifespan = 2.0f;
	}

	void Update(float dt) override;
	void OnCollisionEnter(Actor* other) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;
};