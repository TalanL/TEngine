#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "glm.hpp"
#include "cassert"
#include "miscTypeDef.h"
#include "ExportImportHeader.h"
#include "ExportHeader.h"

using glm::vec3;
namespace GameObjects 
{
	class Component;
	class ENGINE_SHARED GameObject
	{
		int id;

		static const int MAX_COMPONENTS = 10;
		GameObjects::Component* components[MAX_COMPONENTS];
		int numComponents;
	public:
		GameObject* target;
		void setTarget(GameObject* target);
		vec3 position;
		float orientation;
		GameObject();
		bool initialize();
		bool shutDown();
		void addComponent(GameObjects::Component* component);
		void update();
		template<class T>
		T* getComponent() const;
	};

	template<class T>
	T* GameObject::getComponent() const {
		for (int i = 0; i < numComponents; i++)
		{
			T* ret = dynamic_cast<T*>(components[i]);
			if(ret != 0){
				return ret;
			}
		}
		return NULL;
	}
}
#endif