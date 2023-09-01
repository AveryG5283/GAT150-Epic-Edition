#include "JumpDingus3.h"
#include "Core/Core.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Physics/PhysicsSystem.h"

#include <thread>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
	//INFO_LOG("Initializing Engine...");

	minimum::MemoryTracker::Initialize();

	minimum::seedRandom((unsigned int)time(nullptr));
	minimum::setFilePath("assets");

	//our window setup
	minimum::g_renderer.Initialize();
	minimum::g_renderer.CreateWindow("GAT150", 800, 600);

	minimum::g_inputSystem.Initialize();
	minimum::g_audioSystem.Initialize();
	minimum::PhysicsSystem::Instance().Initialize();

	unique_ptr<JumpDingus3> game = make_unique<JumpDingus3>();
	game->Initialize();

	//minimum::g_audioSystem.PlayOneShot("bg_music", true); //song is The Hand of the Queen from the game Rectangle Guy

	bool quit = false;
	while (!quit)
	{
		//update engine
		minimum::g_time.Tick();
		minimum::g_inputSystem.Update();
		if (minimum::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) //if esc is pressed, end the thing
		{
			quit = true;
		}

		//minimum::g_audioSystem.Update();
		minimum::g_particleSystem.Update(minimum::g_time.GetDeltaTime());

		minimum::PhysicsSystem::Instance().Update(minimum::g_time.GetDeltaTime());

		//update game
		game->Update(minimum::g_time.GetDeltaTime());

		minimum::g_renderer.BeginFrame();

		//update draw

		game->Draw(minimum::g_renderer);

		minimum::g_renderer.EndFrame();
	}

	return 0;
}