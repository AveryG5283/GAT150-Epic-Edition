#include "ContactListener.h"
#include "Framework/CollisionComponent.h"
#include "Framework/Actor.h"

namespace minimum
{
	void ContactListener::BeginContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA->GetUserData().pointer && fixtureB->GetUserData().pointer)
		{
			Actor* actorA = reinterpret_cast<Actor*>(fixtureA->GetUserData().pointer);
			Actor* actorB = reinterpret_cast<Actor*>(fixtureB->GetUserData().pointer);

			if (actorA->GetDestroyed() || actorB->GetDestroyed()) return;

			actorA->OnCollisionEnter(actorB);
			actorB->OnCollisionEnter(actorA);
		}
	}

	void ContactListener::EndContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA->GetUserData().pointer && fixtureB->GetUserData().pointer)
		{
			Actor* actorA = reinterpret_cast<Actor*>(fixtureA->GetUserData().pointer);
			Actor* actorB = reinterpret_cast<Actor*>(fixtureB->GetUserData().pointer);

			if (actorA->GetDestroyed() || actorB->GetDestroyed()) return;

			actorA->OnCollisionExit(actorB);
			actorB->OnCollisionExit(actorA);
		}
	}
}