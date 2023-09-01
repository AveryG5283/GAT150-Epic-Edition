#pragma once
#include "Framework/Actor.h"
#include "Framework/PhysicsComponent.h"


namespace minimum {
	class Player : public Actor
	{
	public:
		CLASS_DECLARATION(Player)

		Player() = default;

		/*Player(float speed, float turnRate, const Transform& transform) :
			Actor{ transform },
			m_speed{ speed },
			m_turnRate{ turnRate }
		{};*/

		bool Initialize() override;

		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;

	private:
		float speed = 0;
		float turnRate = 0;

		PhysicsComponent* m_physicsComponent = nullptr;
	};
}