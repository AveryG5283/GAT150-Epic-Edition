#pragma once
#include "Framework/Actor.h"

class Enemy2 : public minimum::Actor
{
public:
	Enemy2(float speed, float turnRate, const minimum::Transform transform, const std::shared_ptr<minimum::Model> model) :
		Actor{ transform, model },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{};

	void Update(float dt) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;
};