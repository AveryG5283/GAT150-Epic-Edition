#include "Enemy2.h"
#include "Player.h"
#include "Weapon.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Emitter.h"

#include "Game/SpaceBlast3000.h"

void Enemy2::Update(float dt)
{
	Actor::Update(dt);

	minimum::vec2 forward = minimum::vec2(0, -1).Rotate(m_transform.rotation);
	Player* player = m_scene->GetActor<Player>(); //T* is replaced by player 
	if (player)
	{
		minimum::vec2 direction = player->m_transform.position - m_transform.position;

		float turnAngle = minimum::vec2::SignedAngle(forward, direction.Normalized());

		m_transform.rotation += turnAngle * dt;

	}

	m_transform.position += forward * m_speed * minimum::g_time.GetDeltaTime();
	m_transform.position.x = minimum::Wrap(m_transform.position.x, (float)minimum::g_renderer.GetWidth()); //if i dont cast these to a float he stutters and dies
	m_transform.position.y = minimum::Wrap(m_transform.position.y, (float)minimum::g_renderer.GetHeight());

}