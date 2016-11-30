#include "PhysicsComponent.h"

void GameObjects::PhysicsComponent::update()
{
	parent->orientation += angularVelocity;
	parent->position += velocity;
}

void GameObjects::PhysicsComponent::setData(float speed)
{
	this->speed = speed;
}
