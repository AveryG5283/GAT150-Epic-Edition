#pragma once
#include "Font.h"
#include "Core/Color.h"

#include <string>
#include <memory>

struct SDL_Texture;

namespace minimum
{

	class Renderer;

	class Text
	{
	public:
		//<create a default constructor>
		Text() = default;
		//Text(<a shared pointer of Font type> font) : m_font{ font } { }
		Text(std::shared_ptr<Font> font) : m_font{ font } { }
		~Text();

		void Create(Renderer& renderer, const std::string& text, const Color& color);
		void Draw(Renderer& renderer, int x, int y);
		void Draw(Renderer& renderer, const class Transform& transform);



	private:
		//<a shared pointer of Font type> m_font;
		std::shared_ptr<Font> m_font;
		//m_font
		struct SDL_Texture* m_texture = nullptr;
	};
}
