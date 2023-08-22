#include "Enemy.h"
#include "Player.h"
#include "Weapon.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Emitter.h"
#include "Framework/Emitter.h"
#include "Framework/PhysicsComponent.h"
#include "Framework/CollisionComponent.h"
#include "Framework/RenderComponent.h"

#include "Game/SpaceBlast3000.h"


namespace minimum {
	bool Enemy::Initialize()
	{
		Actor::Initialize();

		auto collisionComponent = GetComponent<minimum::CollisionComponent>();

		if (collisionComponent)
		{
			auto renderComponent = GetComponent<minimum::RenderComponent>();
			if (renderComponent)
			{
				float scale = transform.scale;
				collisionComponent->m_radius = renderComponent->GetRadius() * scale;
			}
		}

		return true;

	}

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		minimum::vec2 forward = minimum::vec2(0, -1).Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>(); //T* is replaced by player 
		if (player)
		{
			minimum::vec2 direction = player->transform.position - transform.position;

			float turnAngle = minimum::vec2::SignedAngle(forward, direction.Normalized());

			transform.rotation += turnAngle * dt;
		}

		transform.position += forward * m_speed * minimum::g_time.GetDeltaTime();
		transform.position.x = minimum::Wrap(transform.position.x, (float)minimum::g_renderer.GetWidth()); //if i dont cast these to a float he stutters and dies
		transform.position.y = minimum::Wrap(transform.position.y, (float)minimum::g_renderer.GetHeight());

	}

	void Enemy::OnCollision(Actor* other)
	{
		//dynamic_cast<Player*>(other) returns a player or null

		if (other->tag == "Player")
		{
			//create explosion
			minimum::EmitterData data;
			data.burst = true;
			data.burstCount = 100;
			data.spawnRate = 0;
			data.angle = 0;
			data.angleRange = minimum::Pi;
			data.lifetimeMin = 0.5f;
			data.lifetimeMin = 1.0f;
			data.speedMin = 50;
			data.speedMax = 250;
			data.damping = 0.5f;
			data.color = minimum::Color{ 1, 0, 0, 1 };

			minimum::Transform transform{transform.position, 0, 1};
			auto emitter = std::make_unique<minimum::Emitter>(transform, data);
			//emitter->m_lifespan = 1.0f; rewrote this to be better?
			emitter->SetLifespan(3.0f);
			m_scene->Add(std::move(emitter));

			m_game->AddPoints(100);
			destroyed = true;
			//minimum::g_audioSystem.PlayOneShot("dead");
			dynamic_cast<SpaceBlast3000*>(m_game)->SetState(SpaceBlast3000::eState::Game);
		}
	}
}
