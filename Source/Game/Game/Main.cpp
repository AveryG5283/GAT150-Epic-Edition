#include "Core/Core.h" //linked to a bunch of directories
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Input/InputSystem.h"
#include "Framework/Scene.h"
#include "Framework/Emitter.h"
#include "Player.h"
#include "Enemy.h"
#include "Audio/AudioSystem.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Framework/ResourceManager.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Texture.h"

#include "SpaceBlast3000.h"

#include <thread>
#include <iostream> //searches the system instead
#include <vector>
#include <array>
#include <map>

using namespace std;

class Star
{
public:
	Star(const minimum::Vector2& pos, const minimum::Vector2& vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}

	void Update()
	{
		m_pos += m_vel * minimum::g_time.GetDeltaTime();
	}

	void Draw(minimum::Renderer& renderer)
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	minimum::vec2 m_pos;
	minimum::vec2 m_vel;
};

void print_arg(int count, ...)
{
	va_list args;

	va_start(args, count);
	for (int i = 0; i < count; ++i)
	{
		std::cout << va_arg(args, const char*) << std::endl;
	}
	va_end(args);
}

int main(int argc, char* argv[])
{	
	print_arg(3, "hello", "world", "goodbye");

	INFO_LOG("Oh hellooo");

	minimum::MemoryTracker::Initialize();

	minimum::seedRandom((unsigned int)time(nullptr));
	minimum::setFilePath("assets");

	//our window setup
	minimum::g_renderer.Initialize();
	minimum::g_renderer.CreateWindow("CSC196", 800, 600);

	minimum::g_inputSystem.Initialize();
	minimum::g_audioSystem.Initialize();
	

	unique_ptr<SpaceBlast3000> game = make_unique<SpaceBlast3000>();
	game->Initialize();

	vector<Star> stars;

	bool quit = false;

	// create texture

	// da game loop
	while (!quit)
	{

		//update engine
		minimum::g_time.Tick();
		minimum::g_inputSystem.Update();
		minimum::g_audioSystem.Update();
		minimum::g_particleSystem.Update(minimum::g_time.GetDeltaTime());

		//update game
		game->Update(minimum::g_time.GetDeltaTime());

		minimum::g_renderer.SetColor(0, 0, 0, 0);
		minimum::g_renderer.BeginFrame(); 

		if (minimum::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		//update draw
		minimum::Vector2 vel(1.0f, 0.3f);

		for (auto& star : stars)
		{
			star.Update();

			if (star.m_pos.x >= minimum::g_renderer.GetWidth()) star.m_pos.x = 0;
			if (star.m_pos.y >= minimum::g_renderer.GetHeight()) star.m_pos.y = 0;

			minimum::g_renderer.SetColor(minimum::random(256), minimum::random(256), minimum::random(256), 255);
			minimum::g_renderer.DrawPoint(star.m_pos.x, star.m_pos.y);
		}

		game->Draw(minimum::g_renderer);

		//minimum::g_renderer.DrawTexture(texture.get(), 200.0f, 200.0f, 0.0f);

		minimum::g_renderer.EndFrame();
	}

	stars.clear();

	return 0;
}