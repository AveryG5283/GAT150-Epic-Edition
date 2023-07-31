#include "SpaceBlast3000.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Framework/Scene.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/ModelManager.h"
#include "Framework/Emitter.h"

bool SpaceBlast3000::Initialize()
{
	//create font / text objects
	m_font = std::make_shared<minimum::Font>("QuirkyRobot.ttf", 24);
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
		}
		break;
	case SpaceBlast3000::eState::StartGame:
		m_score = 0;
		enemy3Summoned = false;
		m_state = eState::StartLevel;
		break;
	case SpaceBlast3000::eState::StartLevel:
		m_scene->RemoveAll();
	{
		std::unique_ptr<Player> player = std::make_unique<Player>(20.0f, minimum::Pi, minimum::Transform{ { 400, 300}, 0, 4.5f }, minimum::g_manager.Get("ship.txt"));
		player->m_tag = "Player";
		player->m_game = this;
		player->SetDamping(0.9f);
		m_scene->Add(std::move(player));

		std::unique_ptr<Enemy2> enemy2 = std::make_unique<Enemy2>(100.0f, minimum::Pi, minimum::Transform{ { 100, 100 }, 0, 5.5f }, minimum::g_manager.Get("enemy2.txt"));
		enemy2->m_tag = "Enemy2";
		enemy2->m_game = this;
		m_scene->Add(std::move(enemy2));

		std::unique_ptr<Enemy2> enemy22 = std::make_unique<Enemy2>(170.0f, minimum::Pi, minimum::Transform{ { 650, 600 }, 0, 5.5f }, minimum::g_manager.Get("enemy2.txt"));
		enemy22->m_tag = "Enemy2";
		enemy22->m_game = this;
		m_scene->Add(std::move(enemy22));
	}

		m_state = eState::Game;
		break;

	case SpaceBlast3000::eState::Game:
	//	minimum::g_audioSystem.PlayOneShot("bg music");
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0;
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(minimum::randomf(20.0f, 200.0f), minimum::Pi, minimum::Transform{ { minimum::random(800), minimum::random(600)}, minimum::randomf(minimum::twoPi), 3 }, minimum::g_manager.Get("enemy1.txt"));
			enemy->m_tag = "Enemy";
			enemy->m_game = this;
			m_scene->Add(std::move(enemy));

			if (!enemy3Summoned && m_score >= 1000)
			{
				std::unique_ptr<Enemy2> enemy23 = std::make_unique<Enemy2>(225.0f, minimum::Pi, minimum::Transform{ { 50, 50 }, 0, 7.5f }, minimum::g_manager.Get("enemy2.txt"));
				enemy23->m_tag = "Enemy2";
				enemy23->m_game = this;
				m_scene->Add(std::move(enemy23));
				enemy3Summoned = true;
			}


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
	if (m_state == eState::Title)
	{
		m_titleText->Draw(renderer, 400, 300);
	}

	if (m_state == eState::GameOver)
	{
		m_gameOverText->Draw(renderer, 400, 300);
	}

	m_scoreText->Draw(renderer, 40, 40);

	m_scene->Draw(renderer);

}
