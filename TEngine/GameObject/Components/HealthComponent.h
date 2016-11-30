#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H
#include "GameObject/Component.h"
#include "ExportHeader.h"
#include "iostream"
using std::ifstream;
using std::ios;
using std::cout;
using std::endl;
namespace GameObjects 
{
	class ENGINE_SHARED HealthComponent :public Component
	{
		int* health; 
		 
	
	public:
		int* alive;
		int deltaHealth;
		void setData(int* MaxHealth, int* living);

		bool initalize();

		bool shutdown();

		void update();
	};
}
#endif

