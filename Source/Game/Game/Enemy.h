#pragma once
#include "Framework/Actor.h"
#include "Framework/Emitter.h"
#include "Framework/PhysicsComponent.h"

namespace minimum {
	class Enemy : public Actor
	{
	public:
		CLASS_DECLARATION(Enemy)

		Enemy() = default;

		/*Enemy(float speed, float turnRate, const minimum::Transform transform) :
			Actor{ transform },
			speed{ speed },
			turnRate{ turnRate }
		{
			fireRate = 3.0f;
			fireTimer = fireRate;
		};*/

		bool Initialize() override;

		void Update(float dt) override;
		void OnCollisionEnter(Actor* oother) override;


	private:
		float speed = 0;
		float turnRate = 0;

		float fireRate = 0;
		float fireTimer = 0; //how often it shoots

		float m_health = 10;

		minimum::PhysicsComponent* m_physicsComponent = nullptr;
		//float m_damage = 10;
	};
}