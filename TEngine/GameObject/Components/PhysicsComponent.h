#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H
#include "GameObject/Component.h"
#include "ExportHeader.h"
#include "glm.hpp"
using glm::vec3;
namespace GameObjects 
{
	class ENGINE_SHARED PhysicsComponent : public Component
	{
	public:
		float speed;
		vec3 velocity;
		vec3 acceleration;
		float angularVelocity;
		PhysicsComponent() { angularVelocity = 0.0f;};
		virtual void update();
		void setData(float speed);
	};
}
#endif