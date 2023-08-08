#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"

namespace minimum 
{
	class SpriteComponent : public Component
	{
	public:
		void Update(float dt) override;
		void Draw(class Renderer& renderer);

	public:
		res_t<Texture> m_texture;


	private:



	};
}