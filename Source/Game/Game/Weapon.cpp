#include "Weapon.h"

void Weapon::Update(float dt)
{
    Actor::Update(dt);

    minimum::vec2 forward = minimum::vec2(0, -1).Rotate(m_transform.rotation);
    m_transform.position += forward * m_speed * minimum::g_time.GetDeltaTime();

    m_transform.position.x = minimum::Wrap(m_transform.position.x, (float)minimum::g_renderer.GetWidth());
    m_transform.position.y = minimum::Wrap(m_transform.position.y, (float)minimum::g_renderer.GetHeight());
}

void Weapon::OnCollision(Actor* other)
{
    if (other->m_tag != m_tag)
    {
        m_destroyed = true;
    }
}