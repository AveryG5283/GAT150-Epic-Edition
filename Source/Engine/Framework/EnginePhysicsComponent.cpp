#include "EnginePhysicsComponent.h"
#include "Actor.h"

namespace minimum
{

	void EnginePhysicsComponent::Update(float dt)
	{
		m_owner->m_transform.position += m_velocity * dt;
		m_velocity *= std::pow(1.0f - m_damping, dt);
	}

	void EnginePhysicsComponent::ApplyForce(const vec2& force)
	{
		m_velocity += force;
	}


}
