#include "Scene.h"
#include "Framework/CollisionComponent.h"

namespace minimum
{
	bool Scene::Initialize()
	{
		for (auto& actor : m_actors) actor->Initialize();
		

		return true;
	}
	void Scene::Update(float dt)
	{
		//remove destroyed actors
		auto iter = m_actors.begin(); //contains our actor
		while (iter != m_actors.end())
		{
			if (!(*iter)->active) (*iter)->Update(dt);

			(*iter)->Update(dt);
			((*iter)->destroyed) ? iter = m_actors.erase(iter) : iter++;
		}

		//check collisions
		for (auto iter1 = m_actors.begin(); iter1 != m_actors.end(); iter1++)
		{
			for (auto iter2 = std::next(iter1, 1); iter2 != m_actors.end(); iter2++) //helps prevent duplicate checks
			{ //if distance >sum of both radius
				CollisionComponent* collision1 = (*iter1)->GetComponent<CollisionComponent>();
				CollisionComponent* collision2 = (*iter2)->GetComponent<CollisionComponent>();

				float distance = (*iter1)->transform.position.Distance((*iter2)->transform.position);

				if (collision1 == nullptr || collision2 == nullptr) continue;

				if (collision1->CheckCollision(collision2))
				{
					//boom
					(*iter1)->OnCollisionEnter(iter2->get()); //gets the raw pointer from iter 2 or i guess the object?
					(*iter2)->OnCollisionEnter(iter1->get());
				}
			}
		}
	}

	void Scene::Draw(Renderer& renderer)
	{
		for (auto& actor : m_actors)
		{
			if (actor->active) actor->Draw(renderer);
		}
	}

	void Scene::Add(std::unique_ptr<Actor> actor)
	{
		actor->m_scene = this;
		m_actors.push_back(std::move(actor));
	}

	void Scene::RemoveAll(bool force)
	{
		auto iter = m_actors.begin(); //contains our actor
		while (iter != m_actors.end())
		{
			(force || !(*iter)->persistent) ? iter = m_actors.erase(iter) : iter++;
		}

	}
	bool Scene::Load(const std::string& filename)
	{
		rapidjson::Document document;

		if (!Json::Load(filename, document))
		{
			ERROR_LOG("Could not load scene file: " << filename);
			return false;
		}

		Read(document); // breaks inside of here

		return true;
	}

	void Scene::Read(const json_t& value)
	{
		if (HAS_DATA(value, actors) && GET_DATA(value, actors).IsArray())
		{
			for (auto& actorValue : GET_DATA(value, actors).GetArray())
			{
				std::string type;
				READ_DATA(actorValue, type);
				auto actor = CREATE_CLASSBASE(Actor, type);
				actor->Read(actorValue); // breaks inside of here on second loop through, not first

				if (actor->prototype)
				{
					std::string name = actor->name;
					Factory::Instance().RegisterPrototype(name, std::move(actor));
				}
				else
				{
					Add(std::move(actor));
				}

			}
		}
	}
}