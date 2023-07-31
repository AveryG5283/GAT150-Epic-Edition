#include "Particle.h"
#include "../Renderer/Renderer.h"
#include "Core/Core.h"

void minimum::Particle::Update(float dt)
{
    m_data.lifetimer += dt;
    if (m_data.lifetimer >= m_data.lifetime)
    {
        m_isActive = false;
        return;
    }
    m_data.prevPosition = m_data.position;
    m_data.position += m_data.velocity * dt;
    m_data.velocity *= std::pow(1.0f - m_data.damping, dt);
}

void minimum::Particle::Draw(minimum::Renderer& renderer)
{
    renderer.SetColor(minimum::Color::ToInt(m_data.color.r), minimum::Color::ToInt(m_data.color.g), minimum::Color::ToInt(
        m_data.color.b), minimum::Color::ToInt(m_data.color.a));
    renderer.DrawLine(m_data.position.x, m_data.position.y, m_data.prevPosition.x, m_data.prevPosition.y);
}