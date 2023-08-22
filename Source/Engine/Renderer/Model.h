#pragma once
#include "Framework/Resource.h"
#include "Core/Vector2.h"
#include "Core/Transform.h"
#include "Core/Color.h"
#include <vector>

namespace minimum
{
	class Renderer;

	class Model : public Resource
	{
	public:
		Model() = default;
		Model(const std::vector<vec2>& points) : m_points{ points } {}

		virtual bool Create(std::string filename, ...) override;
		bool Load(const std::string& filename);
		void Draw(Renderer& renderer, const vec2& position, float rotation, float scale);
		void Draw(Renderer& renderer, const Transform& transform);

		float GetRadius();
	private:
		std::vector<vec2> m_points;
		Color m_color;
		float m_radius = 0;

	};
}