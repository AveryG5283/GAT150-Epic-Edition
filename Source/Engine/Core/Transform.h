#pragma once
#include "Vector2.h"

namespace minimum
{
	class Transform
	{
	public:
		minimum::vec2 position;
		float rotation = 0;
		float scale = 1.0f;

	public:
		Transform(const vec2& position, float rotation, float scale = 1.0f) :
			position{ position },
			rotation{ rotation },
			scale{ scale }
		{}

	};
}