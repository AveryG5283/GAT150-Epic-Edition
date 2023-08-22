#pragma once
#include "Framework/Actor.h"

namespace minimum {
	class Enemy2 : public minimum::Actor
	{
	public:
		Enemy2(float speed, float turnRate, const minimum::Transform transform) :
			Actor{ transform },
			m_speed{ speed },
			m_turnRate{ turnRate }
		{};

		void Update(float dt) override;
		bool Initialize() override;

	private:
		float m_speed = 0;
		float m_turnRate = 0;
	};
}