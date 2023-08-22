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
		//create player
		auto player = std::make_unique<minimum::Player>(20.0f, minimum::Pi, minimum::Transform{{ 400, 300}, 0, 4.5f});
		player->tag = "Player";
		player->m_game = this;

		//create components

		auto renderComponent = CREATE_CLASS(SpriteComponent);
		renderComponent->m_texture = GET_RESOURCE(minimum::Texture, "rocket.png", minimum::g_renderer);
		//renderComponent->m_texture = minimum::g_resources.Get<minimum::Texture>("rocket.png");
		player->AddComponent(std::move(renderComponent));

		auto physicsComponent = CREATE_CLASS(EnginePhysicsComponent);
		physicsComponent->m_damping = 0.9f;
		player->AddComponent(std::move(physicsComponent));

		auto collisionComponent = CREATE_CLASS(CircleCollisionComponent);		
		collisionComponent->m_radius = 30.0f;
		player->AddComponent(std::move(collisionComponent));

		player->Initialize();
		m_scene->Add(std::move(player));




		auto enemy2 = std::make_unique<minimum::Enemy2>(20.0f, minimum::Pi, minimum::Transform{{ 400, 300}, 0, 4.5f});
		enemy2->tag = "Enemy";
		enemy2->m_game = this;

		//create components
		auto rrenderComponent = CREATE_CLASS(SpriteComponent);
		rrenderComponent->m_texture = GET_RESOURCE(minimum::Texture, "rocket.png", minimum::g_renderer);
		enemy2->AddComponent(std::move(renderComponent));

		auto pphysicsComponent = CREATE_CLASS(EnginePhysicsComponent);
		pphysicsComponent->m_damping = 0.9f;
		enemy2->AddComponent(std::move(physicsComponent));

		auto ccollisionComponent = CREATE_CLASS(CircleCollisionComponent);
		ccollisionComponent->m_radius = 30.0f;
		enemy2->AddComponent(std::move(ccollisionComponent));

		enemy2->Initialize();
		m_scene->Add(std::move(enemy2));
	}

		m_state = eState::Game;
		break;

	case SpaceBlast3000::eState::Game:
	//	minimum::g_audioSystem.PlayOneShot("bg music");
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0;
			auto enemy= std::make_unique<minimum::Enemy>(20.0f, minimum::Pi, minimum::Transform{{ 400, 300}, 0, 4.5f});
			enemy->tag = "Enemy";
			enemy->m_game = this;

			//create components
			auto renderComponent = CREATE_CLASS(SpriteComponent);
			renderComponent->m_texture = GET_RESOURCE(minimum::Texture, "rocket.png", minimum::g_renderer);
			enemy->AddComponent(std::move(renderComponent));

			auto physicsComponent = CREATE_CLASS(EnginePhysicsComponent);
			physicsComponent->m_damping = 0.9f;
			enemy->AddComponent(std::move(physicsComponent));

			auto ccollisionComponent = CREATE_CLASS(CircleCollisionComponent);
			ccollisionComponent->m_radius = 30.0f;
			enemy->AddComponent(std::move(ccollisionComponent));

			enemy->Initialize();
			m_scene->Add(std::move(enemy));

			/*if (!enemy3Summoned && m_score >= 1000)
			{
				std::unique_ptr<Enemy2> enemy23 = std::make_unique<Enemy2>(225.0f, minimum::Pi, minimum::Transform{ { 50, 50 }, 0, 7.5f });
				enemy23->tag = "Enemy2";
				enemy23->m_game = this;
				m_scene->Add(std::move(enemy23));
				enemy3Summoned = true;
			}*/


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
