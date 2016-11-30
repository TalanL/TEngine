#include "HealthComponent.h"
#include "Qt\qdebug.h"
#include "iostream"
bool GameObjects::HealthComponent::initalize()
{
	deltaHealth = 0;
	return true;
}

bool GameObjects::HealthComponent::shutdown()
{
	return true;
}

void GameObjects::HealthComponent::update()
{
	*health = *health + deltaHealth;
	deltaHealth = 0;
	if( *health < 0){
		*alive = -1;
	}
}

void GameObjects::HealthComponent::setData(int* MaxHealth, int* living)
{
	health = MaxHealth;
	this->alive = living;
}
