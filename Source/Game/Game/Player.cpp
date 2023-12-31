#include "Player.h"
#include "Weapon.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Framework/Emitter.h"
#include "Renderer/Texture.h"

#include "Game/SpaceBlast3000.h"
namespace minimum {
	CLASS_DEFINITION(Player)

	bool Player::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<minimum::PhysicsComponent>();
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

	void Player::Update(float dt)
	{
		Actor::Update(dt);

		//movement
		float rotate = 0;
		if (minimum::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
		if (minimum::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
		//transform.rotation += rotate * m_turnRate * minimum::g_time.GetDeltaTime();
		m_physicsComponent->ApplyTorque(rotate * turnRate);

		float thrust = 0;
		if (minimum::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

		minimum::vec2 forward = minimum::vec2(0, -1).Rotate(transform.rotation);

		m_physicsComponent->ApplyForce(forward * speed * thrust);


		transform.position.x = minimum::Wrap(transform.position.x, (float)minimum::g_renderer.GetWidth());
		transform.position.y = minimum::Wrap(transform.position.y, (float)minimum::g_renderer.GetHeight());

	}

	void Player::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Enemy2")
		{
			minimum::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
		}

		if (other->tag == "Enemy1")
		{

			minimum::EventManager::Instance().DispatchEvent("AddPoints", 100);

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

			minimum::Transform transform{transform.position, 0, 1};
			auto emitter = std::make_unique<minimum::Emitter>(transform, data);
			emitter->SetLifespan(3.0f);
			m_scene->Add(std::move(emitter));
		}

	}

	void Player::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, turnRate);
	}

}