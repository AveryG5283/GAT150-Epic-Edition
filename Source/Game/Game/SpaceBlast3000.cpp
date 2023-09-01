#include "SpaceBlast3000.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy2.h"

#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Framework/RenderComponent.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Framework/Emitter.h"
#include "Framework/EventManager.h"

bool SpaceBlast3000::Initialize()
{
	//create font / text objects
	//m_font = minimum::g_resources.Get<minimum::Font>("QuirkyRobot.ttf", 24);
	m_font = GET_RESOURCE(minimum::Font, "QuirkyRobot.ttf", 24);
	m_scoreText = std::make_unique<minimum::Text>(m_font);
	m_scoreText->Create(minimum::g_renderer, "Score: nothing yet, dumby", minimum::Color{ 1, 1, 1, 1 });

	m_titleText = std::make_unique<minimum::Text>(m_font);
	m_titleText->Create(minimum::g_renderer, "Space  Blast  3000", minimum::Color{ 1, 1, 1, 1 });

	m_gameOverText = std::make_unique<minimum::Text>(m_font);
	m_gameOverText->Create(minimum::g_renderer, "DUDE  YOU  DIED!", minimum::Color{ 1, 1, 1, 1 });

	// load audio

	minimum::g_audioSystem.AddAudio("explosion", "explosion.wav");
	minimum::g_audioSystem.AddAudio("intro", "space blast intro.wav");
	minimum::g_audioSystem.AddAudio("bg music", "space blast bg.wav"); //notably, song is taken from Rectangle Guy

	m_scene = std::make_unique<minimum::Scene>();
	m_scene->Load("scene.json");
	m_scene->Initialize();

	// add events
	//minimum::EventManager::Instance().Subscribe("AddPoints", this, std::bind(&SpaceGame::AddPoints, this, std::placeholders::_1));
	//minimum::EventManager::Instance().Subscribe("OnPlayerDead", this, std::bind(&SpaceGame::OnPlayerDead, this, std::placeholders::_1));
	EVENT_SUBSCRIBE("OnAddPoints", SpaceBlast3000::OnAddPoints);
	EVENT_SUBSCRIBE("OnPlayerDead", SpaceBlast3000::OnPlayerDead);

	return true;
}

bool SpaceBlast3000::Shutdown()
{
	return false;
}

void SpaceBlast3000::Update(float dt)
{

	switch (m_state)
	{
	case SpaceBlast3000::eState::Title:
	//	minimum::g_audioSystem.PlayOneShot("intro");
		if (minimum::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
			//m_scene->GetActorByName<minimum::Actor>("Background")->active = false;
		}
		break;
	case SpaceBlast3000::eState::StartGame:
		m_score = 0;
		enemy3Summoned = false;
		m_state = eState::StartLevel;
		break;
	case SpaceBlast3000::eState::StartLevel:
		m_scene->RemoveAll(true);
	{
			auto player = INSTANTIATE(minimum::Player, "Player");
			player->transform = minimum::Transform{ { 400, 300 }, 0, 1 };
			player->Initialize();
			m_scene->Add(std::move(player));
	}

		m_state = eState::Game;
		break;

	case SpaceBlast3000::eState::Game:
	//	minimum::g_audioSystem.PlayOneShot("bg music");
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			
			//

		}
		break;
	case SpaceBlast3000::eState::GameOver:
		m_scene->RemoveAll();
		if (minimum::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::Title;
		}

		break;
	default:
		break;
	}

	m_scoreText->Create(minimum::g_renderer, std::to_string(m_score), { 1, 1, 1, 1 });
	m_scene->Update(dt);

}

void SpaceBlast3000::Draw(minimum::Renderer& renderer)
{
	m_scene->Draw(renderer);

	if (m_state == eState::Title)
	{
		m_titleText->Draw(renderer, 400, 300);
	}

	if (m_state == eState::GameOver)
	{
		m_gameOverText->Draw(renderer, 400, 300);
	}

	m_scoreText->Draw(renderer, 40, 40);
}

void SpaceBlast3000::OnAddPoints(const minimum::Event& event)
{
	m_score += std::get<int>(event.data);
}

void SpaceBlast3000::OnPlayerDead(const minimum::Event& event)
{
	m_state = eState::GameOver;
}
