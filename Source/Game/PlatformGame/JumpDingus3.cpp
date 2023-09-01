#include "JumpDingus3.h"
#include "Enemy.h"

#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Core/Core.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Framework/EventManager.h"


bool JumpDingus3::Initialize()
{


	//create scene
	m_scene = std::make_unique<minimum::Scene>();
	m_scene->Load("JumpDingus3/Scenes/tilemap.json");
	m_scene->Load("JumpDingus3/Scenes/scene.json");
	m_scene->Initialize();


	return true;
}

bool JumpDingus3::Shutdown()
{
	//nothing yet
	return false;
}

void JumpDingus3::Update(float dt)
{
	switch (m_state)
	{
	case JumpDingus3::Title:

		break;

	case JumpDingus3::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;

		break;

	case JumpDingus3::StartLevel:
		m_scene->RemoveAll(dt);
		m_state = eState::Game;

		break;

	case JumpDingus3::Tutorial:


		break;

	case JumpDingus3::Game:

		break;
	case JumpDingus3::PlayerDeadStart:


		break;

	case JumpDingus3::PlayerDead:

		break;

	case JumpDingus3::GameOverStart:

		break;

	case JumpDingus3::GameOver:

		break;
	
	case JumpDingus3::Win:
		m_scene->Load("JumpDingus3/Scenes/scenewin.json");

		break;

	default:
		break;
	}

	m_scene->Update(dt);
}

void JumpDingus3::Draw(minimum::Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void JumpDingus3::OnAddPoints(const minimum::Event& event)
{
	m_score += std::get<int>(event.data);
}

void JumpDingus3::OnPlayerDead(const minimum::Event& event)
{
	m_lives--;
	m_state = eState::StartLevel;
}