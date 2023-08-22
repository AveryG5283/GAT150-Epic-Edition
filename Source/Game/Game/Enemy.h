#pragma once
#include "Framework/Actor.h"
#include "Framework/Emitter.h"

namespace minimum {
	class Enemy : public minimum::Actor
	{
	public:
		Enemy(float speed, float turnRate, const minimum::Transform transform) :
			Actor{ transform },
			m_speed{ speed },
			m_turnRate{ turnRate }
		{
			m_fireRate = 3.0f;
			m_fireTimer = m_fireRate;
		};

		bool Initialize() override;

		void Update(float dt) override;
		void OnCollision(Actor* oother) override;


	private:
		float m_speed = 0;
		float m_turnRate = 0;


		float m_fireRate = 0;
		float m_fireTimer = 0; //how often it shoots

		float m_health = 10;
		//float m_damage = 10;
	};
}