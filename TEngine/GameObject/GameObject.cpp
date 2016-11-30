#include "GameObject.h"
#include "Component.h"

namespace GameObjects
{
	GameObject::GameObject(){
		numComponents = 0;
		orientation = 0.0f;
	}
	
	bool GameObject::initialize(){
		for(int i = 0; i < numComponents; i++) {
			components[i]->initalize();
		}
		return true;
	}

	bool GameObject::shutDown(){
		for(int i = 0; i < numComponents; i++) {
			components[i]->shutdown();
		}
		return true;
	}
	
	void GameObject::addComponent(Component* component){
		assert(numComponents != MAX_COMPONENTS);
		components[numComponents++] = component;
		component->parent = this;
	}

	void GameObject::update()
	{
		for(int i = 0; i < numComponents; i ++){
			components[i]->update();
		}
	}

	void GameObject::setTarget(GameObject* target)
	{
		this->target= target;
	}

}