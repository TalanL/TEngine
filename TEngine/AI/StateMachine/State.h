#ifndef STATE_H
#define STATE_H
#include "GameObject/GameObject.h"
namespace GameObjects
{
	class State
	{
	public:
		virtual void Enter(GameObject* parent)=0;
		virtual void Execute(GameObject* parent)=0;
		virtual void Exit(GameObject* parent)=0;
		virtual ~State(){};
	};
}

#endif
