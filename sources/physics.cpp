#include "common.h"

namespace
{
	void engineUpdate()
	{
		for (entityClass *e : physicsComponent::component->entities())
		{
			ENGINE_GET_COMPONENT(transform, t, e);
			GAME_GET_COMPONENT(physics, p, e);
			CAGE_ASSERT_RUNTIME(p.acceleration.valid() && p.velocity.valid() && t.position.valid(), p.acceleration, p.velocity, t.position);
			CAGE_ASSERT_RUNTIME(p.angularAcceleration.valid() && p.rotation.valid() && t.orientation.valid(), p.angularAcceleration, p.rotation, t.orientation);
			p.velocity += p.acceleration;
			p.acceleration = vec3();
			p.rotation = p.angularAcceleration * p.rotation;
			p.angularAcceleration = quat();
			t.position += p.velocity;
			t.orientation = p.rotation * t.orientation;
		}
	}

	class callbacksInitClass
	{
		eventListener<void()> engineUpdateListener;
	public:
		callbacksInitClass()
		{
			engineUpdateListener.attach(controlThread().update, 100);
			engineUpdateListener.bind<&engineUpdate>();
		}
	} callbacksInitInstance;
}
