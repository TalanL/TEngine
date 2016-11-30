#ifndef COMPONENT_H
#define COMPONENT_H
#include "GameObject.h"
#include "ExportHeader.h"

namespace GameObjects 
{
	class ENGINE_SHARED Component
	{
		friend class GameObject;
	protected:
		GameObject* parent;
	public:
		virtual bool initalize() { return true;};
		virtual bool shutdown() { return true;};
		virtual void update(){};
	};
}
#endif