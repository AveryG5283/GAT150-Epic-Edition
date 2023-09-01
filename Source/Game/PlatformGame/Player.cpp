#include "Player.h"

#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"

#include "Game/SpaceBlast3000.h"
#include "JumpDingus3.h"

namespace minimum
{
	CLASS_DEFINITION(Player)

		bool Player::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<PhysicsComponent>();
		m_spriteAnimComponent = GetComponent<SpriteAnimRenderComponent>();

		return true;
	}

	void Player::Update(float dt)
	{
		Actor::Update(dt);

		bool onGround = (groundCount > 0);
		vec2 velocity = m_physicsComponent->m_velocity;

		//movement
		float dir = 0; //direction
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 1;


		if (dir && !(g_inputSystem.GetKeyDown(SDL_SCANCODE_P)) && !(g_inputSystem.GetKeyDown(SDL_SCANCODE_O)) && !(g_inputSystem.GetKeyDown(SDL_SCANCODE_S)))
		{
			vec2 forward = vec2{ 1, 0 };
			velocity.x += speed * dir * ((onGround) ? 1 : 0.25f) * dt;
			velocity.x = Clamp(velocity.x, -maxSpeed, maxSpeed);
			m_physicsComponent->SetVelocity(velocity);
		}

		//dash attempt
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_P) && !(g_inputSystem.GetKeyDown(SDL_SCANCODE_S)))
		{
			velocity.x += speed * 1 * ((onGround) ? 1 : 0.25f) * dt * 2;
			velocity.x = Clamp(velocity.x, -maxSpeed * 3, maxSpeed * 3);
			m_physicsComponent->SetVelocity(velocity);
		}

		//dash attempt
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_O) && !(g_inputSystem.GetKeyDown(SDL_SCANCODE_S)))
		{
			velocity.x += speed * -1 * ((onGround) ? 1 : 0.25f) * dt * 2;
			velocity.x = Clamp(velocity.x, -maxSpeed * 3, maxSpeed * 3);
			m_physicsComponent->SetVelocity(velocity);
		}

		//jump
		if (onGround && g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE) && !(g_inputSystem.GetKeyDown(SDL_SCANCODE_P)) && !(g_inputSystem.GetKeyDown(SDL_SCANCODE_O)) && !(g_inputSystem.GetKeyDown(SDL_SCANCODE_S)))
		{
			vec2 up = vec2{ 0, -1 };
			m_physicsComponent->SetVelocity(velocity + (up * jump));
		}

		m_physicsComponent->SetGravityScale((velocity.y > 0) ? 3.2 : 1);

		if ((g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) && !(g_inputSystem.GetKeyDown(SDL_SCANCODE_P)) && !(g_inputSystem.GetKeyDown(SDL_SCANCODE_O)) && !(g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) && !(g_inputSystem.GetKeyDown(SDL_SCANCODE_S)))
		{
			m_spriteAnimComponent->SetSequence("run");
		}
		else if ((g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) && !(g_inputSystem.GetKeyDown(SDL_SCANCODE_P)) && !(g_inputSystem.GetKeyDown(SDL_SCANCODE_O)) && !(g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) && !(g_inputSystem.GetKeyDown(SDL_SCANCODE_S)))
		{
			m_spriteAnimComponent->SetSequence("run1");
		}
		else if(g_inputSystem.GetKeyDown(SDL_SCANCODE_P) && !(g_inputSystem.GetKeyDown(SDL_SCANCODE_S)))
		{
			m_spriteAnimComponent->SetSequence("dash1");
		}
		else if (g_inputSystem.GetKeyDown(SDL_SCANCODE_O) && !(g_inputSystem.GetKeyDown(SDL_SCANCODE_S)))
		{
			m_spriteAnimComponent->SetSequence("dash2");
		}
		else if (g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !(g_inputSystem.GetKeyDown(SDL_SCANCODE_P)) && !(g_inputSystem.GetKeyDown(SDL_SCANCODE_O)) && !(g_inputSystem.GetKeyDown(SDL_SCANCODE_S)))
		{
			m_spriteAnimComponent->SetSequence("jump");
		}
		else if (g_inputSystem.GetKeyDown(SDL_SCANCODE_S))
		{
			m_spriteAnimComponent->SetSequence("crouch?");
		}
		else
		{
			m_spriteAnimComponent->SetSequence("idle");
		}
	}

	void Player::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Enemy")
		{
			//destroyed = true;
		}

		if (other->tag == "Ground") groundCount++;

		if (other->tag == "trophy")
		{
			JumpDingus3::eState::Win;
		}
	}

	void Player::OnCollisionExit(Actor* other)
	{
		if (other->tag == "Ground") groundCount--; 
		if (other->tag == "trophy")
		{
			JumpDingus3::eState::Win;
		}
	}

	void Player::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, maxSpeed);
		READ_DATA(value, jump);
	}
}