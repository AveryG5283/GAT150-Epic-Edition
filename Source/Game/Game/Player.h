#pragma once
#include "Framework/Actor.h"
#include "Framework/PhysicsComponent.h"


namespace minimum {
	class Player : public minimum::Actor
	{
	public:
		Player(float speed, float turnRate, const Transform& transform) :
			Actor{ transform },
			m_speed{ speed },
			m_turnRate{ turnRate }
		{};

		bool Initialize() override;

		void Update(float dt) override;
		void OnCollision(Actor* other) override;

	private:
		float m_speed = 0;
		float m_turnRate = 0;

		minimum::PhysicsComponent* m_physicsComponent = nullptr;
	};
}