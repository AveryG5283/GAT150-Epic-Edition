#include "Actor.h"
#include "Framework/Component.h"
#include "Framework/RenderComponent.h"

namespace minimum
{
	CLASS_DEFINITION(Actor)

	Actor::Actor(const Actor& other)
	{
		name = other.name;
		tag = other.tag;
		lifespan = other.lifespan;
		transform = other.transform;
		m_scene = other.m_scene;
		m_game = other.m_game;
	}

	bool Actor::Initialize()
	{
		for (auto& component : components)
		{
			component->Initialize();
		}

		return true;
	}

	void Actor::OnDestroy()
	{
		for (auto& component : components)
		{
			component->OnDestroy();
		}
	}

	void Actor::Update(float dt)
	{
		if (lifespan != -1)
		{
			lifespan -= dt;
			destroyed = (lifespan <= 0);
		}

		for (auto& component : components)
		{
			component->Update(dt);
		}
	}

	void Actor::Draw(minimum::Renderer& renderer)
	{
		for (auto& component : components)
		{
			RenderComponent* r_component = dynamic_cast<RenderComponent*>(component.get());
			if (r_component)
			{
				r_component->Draw(renderer);
			}
		}

	}

	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		components.push_back(std::move(component)); //this gives me error ;/
	}

	void Actor::Read(const json_t& value)
	{
		Object::Read(value);

		READ_DATA(value, tag);
		READ_DATA(value, lifespan);
		READ_DATA(value, persistent);
		READ_DATA(value, prototype);

		if (HAS_DATA(value, transform)) transform.Read(GET_DATA(value, transform));

		if (HAS_DATA(value, components) && GET_DATA(value, components).IsArray())
		{
			for (auto& componentValue : GET_DATA(value, components).GetArray())
			{
				std::string type;
				READ_DATA(componentValue, type);

				auto component = CREATE_CLASSBASE(Component, type);
				component->Read(componentValue);

				AddComponent(std::move(component)); //have to move it cause its a unique pointer
			}
		}
	}
}