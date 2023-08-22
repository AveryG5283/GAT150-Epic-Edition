#pragma once
#include "Core/Core.h"
#include "Core/Vector2.h"

namespace minimum
{
    class Renderer;

    struct ParticleData
    {
        minimum::vec2 position;
        minimum::vec2 prevPosition;
        minimum::vec2 velocity;

        float damping = 0;

        minimum::Color color;

        float lifetimer = 0;
        float lifetime = 0;
    };

    class Particle
    {
    public:
        Particle() = default;
        void Initialize(const ParticleData& data)
        {
            m_data = data;
            m_isActive = true;
        }
        void Update(float dt);
        void Draw(minimum::Renderer& renderer);
        friend class ParticleSystem;
    private:
        ParticleData m_data;
        bool m_isActive = false;
    };
}