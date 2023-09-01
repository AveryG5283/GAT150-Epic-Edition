#include "Enemy2.h"
#include "Player.h"
#include "Weapon.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

#include "Game/SpaceBlast3000.h"

namespace minimum {

	CLASS_DEFINITION(Enemy2)

	void Enemy2::Update(float dt)
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

		transform.position += forward * speed * minimum::g_time.GetDeltaTime();
		transform.position.x = minimum::Wrap(transform.position.x, (float)minimum::g_renderer.GetWidth()); //if i dont cast these to a float he stutters and dies
		transform.position.y = minimum::Wrap(transform.position.y, (float)minimum::g_renderer.GetHeight());

	}

	bool Enemy2::Initialize()
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

	void Enemy2::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, turnRate);
	}

}
