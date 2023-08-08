#pragma once
#include "PhysicsComponent.h"

namespace minimum
{

	class EnginePhysicsComponent : public PhysicsComponent
	{




		// Inherited via PhysicsComponent
		virtual void Update(float dt) override;

		virtual void ApplyForce(const vec2& force) override;

	};

}