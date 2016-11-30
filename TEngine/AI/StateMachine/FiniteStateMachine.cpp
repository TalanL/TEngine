#include "FiniteStateMachine.h"

void GameObjects::FiniteStateMachine::setCurrentState(State* s)
{
	currentState = s;
}

void GameObjects::FiniteStateMachine::setGlobalState(State* s)
{
	globalState = s;
}

void GameObjects::FiniteStateMachine::setLastState(State* s)
{
	lastState = s;

}

bool GameObjects::FiniteStateMachine::initalize()
{
	setLastState(NULL);
	setCurrentState(NULL);
	return true;

}

bool GameObjects::FiniteStateMachine::shutdown()
{
	return true;
}

void GameObjects::FiniteStateMachine::update()
{
	if(globalState)
	{
		globalState->Execute(parent);
	}

	if(currentState)
	{
		currentState->Execute(parent);
	}
}

void GameObjects::FiniteStateMachine::changeState(State* newState)
{
	setLastState(currentState);
	if(currentState)
	{
		currentState->Exit(parent);
	}
	setCurrentState(newState);
	currentState->Enter(parent);
}

void GameObjects::FiniteStateMachine::setDate(GameObject* t)
{
	target = t;
}
