#include "Player.h"
#include "Weapon.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Framework/Emitter.h"

#include "Game/SpaceBlast3000.h"

void Player::Update(float dt)
{
	Actor::Update(dt);

	//movement
	float rotate = 0;
	if (minimum::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (minimum::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * minimum::g_time.GetDeltaTime();

	float thrust = 0;
	if (minimum::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

	minimum::vec2 forward = minimum::vec2(0, -1).Rotate(m_transform.rotation);
	AddForce(forward * m_speed * thrust); //moves player

	m_transform.position.x = minimum::Wrap(m_transform.position.x, (float)minimum::g_renderer.GetWidth());
	m_transform.position.y = minimum::Wrap(m_transform.position.y, (float)minimum::g_renderer.GetHeight());

}

void Player::OnCollision(Actor* other)
{
	if (other->m_tag == "Enemy2")
	{
		dynamic_cast<SpaceBlast3000*>(m_game)->SetState(SpaceBlast3000::eState::GameOver);
	}

	if (other->m_tag == "Enemy1")
	{
		minimum::EmitterData data;
		data.burst = true;
		data.burstCount = 100;
		data.spawnRate = 0;
		data.angle = 0;
		data.angleRange = minimum::Pi;
		data.lifetimeMin = 50.5f;
		data.lifetimeMax = 100.5f;
		data.speedMin = 50;
		data.speedMax = 250;
		data.damping = 0.5f;
		data.color = minimum::Color{ 1, 0, 0, 1 };

		minimum::Transform transform{m_transform.position, 0, 1};
		auto emitter = std::make_unique<minimum::Emitter>(m_transform, data);
		emitter->SetLifespan(3.0f);
		m_scene->Add(std::move(emitter));
	}


}