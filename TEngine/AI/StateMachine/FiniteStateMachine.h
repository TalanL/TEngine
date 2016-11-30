#ifndef FINITESTATEMACHINE_H
#define FINITESTATEMACHINE_H
#include "GameObject/Component.h"
#include "GameObject/GameObject.h"
#include "ExportHeader.h"
#include "State.h"

namespace GameObjects 
{
	class ENGINE_SHARED FiniteStateMachine :public Component
	{
		GameObject* target;

		State* currentState;
		State* lastState;
		State* globalState;

	public:
		void setCurrentState(State* s);
		void setGlobalState(State* s);
		void setLastState(State* s);

		bool initalize();
		void setDate(GameObject* t);
		bool shutdown();

		void update();

		void changeState(State* newState);
	};
}
#endif
