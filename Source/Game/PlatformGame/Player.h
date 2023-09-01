#pragma once
#include "Framework/Framework.h"
#include "Framework/PhysicsComponent.h"
#include "Framework/SpriteAnimRenderComponent.h"

namespace minimum
{
	class Player : public Actor
	{
	public:
		CLASS_DECLARATION(Player)

			Player() = default;

		bool Initialize() override;

		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;

	private:
		float speed = 0;
		float jump = 0;
		float maxSpeed = 0;
		int groundCount = 0;

		PhysicsComponent* m_physicsComponent = nullptr;
		SpriteAnimRenderComponent* m_spriteAnimComponent = nullptr;
	};
}