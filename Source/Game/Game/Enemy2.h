#pragma once
#include "Framework/Actor.h"

namespace minimum {
	class Enemy2 : public Actor
	{
	public:

		CLASS_DECLARATION(Enemy2)

		Enemy2() = default;

		/*Enemy2(float speed, float turnRate, const minimum::Transform transform) :
			Actor{ transform },
			m_speed{ speed },
			m_turnRate{ turnRate }
		{};*/

		void Update(float dt) override;
		bool Initialize() override;

	private:
		float speed = 0;
		float turnRate = 0;
	};
}