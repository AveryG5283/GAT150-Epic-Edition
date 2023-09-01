#include "Core/Core.h" //linked to a bunch of directories
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Framework/Framework.h"
#include "Player.h"
#include "Enemy.h"
#include "Audio/AudioSystem.h"

#include "Physics/PhysicsSystem.h"

#include "SpaceBlast3000.h"

#include <thread>
#include <iostream> //searches the system instead
#include <vector>
#include <array>
#include <map>
#include <functional>


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

void print(int i)
{
	cout << i << endl;
}

int add(int butt, int hole)
{
	int butthole = butt + hole;
	return butthole;
}

class A
{
public:
	int add(int butt, int hole)
	{
		return butt + hole;
	}
};

union Data
{
	int i;
	bool b;
	char c[6];
};


int main(int argc, char* argv[])
{	

	Data data;
	data.b = true;

	cout << data.i << endl;

	void (*func_ptr)(int) = &print;

	func_ptr(5);

	std::function<int(int, int)> op;
	op = add;
	cout << op(35, 34) << endl;

	A a;
	op = std::bind(&A::add, &a, std::placeholders::_1, std::placeholders::_2);
	cout << op(42, 27) << endl;

	INFO_LOG("Initialize Engine...");

	minimum::MemoryTracker::Initialize();

	minimum::seedRandom((unsigned int)time(nullptr));
	minimum::setFilePath("assets");

	//our window setup
	minimum::g_renderer.Initialize();
	minimum::g_renderer.CreateWindow("CSC196", 800, 600);

	minimum::g_inputSystem.Initialize();
	minimum::g_audioSystem.Initialize();
	minimum::PhysicsSystem::Instance().Initialize();

	rapidjson::Document document;
	minimum::Json::Load("json.txt", document);

	std::string str;
	minimum::Json::Read(document, "string", str);
	std::cout << str << std::endl;

	bool b;
	minimum::Json::Read(document, "boolean", b);
	std::cout << b << std::endl;

	float f;
	minimum::Json::Read(document, "float", f);
	std::cout << f << std::endl;


	

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

		minimum::PhysicsSystem::Instance().Update(minimum::g_time.GetDeltaTime());

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