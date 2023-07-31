#include "Actor.h"

namespace minimum
{
	void Actor::Update(float dt)
	{
		if (m_lifespan != m_lifespan)
		{
			m_lifespan = m_lifespan - dt;
		}
		if (m_lifespan <= 0) m_destroyed = true;

		m_transform.position += m_velocity * dt;
		m_velocity *= std::pow(1.0f - m_damping, dt);
	}

	void Actor::Draw(minimum::Renderer& renderer)
	{
		m_model->Draw(renderer, m_transform);
	}
}