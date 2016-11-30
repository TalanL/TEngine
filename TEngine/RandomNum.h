#ifndef RANDOMNUM_H
#define RANDOMNUM_H
#include "glm.hpp"
#include "stdlib.h"
const float TWO_PI = 2*3.141926f;
struct RandomNum
{
	float randomFloat()
	{
		return (float) rand() / RAND_MAX;
	}
	
	float randomInRange(float min, float max)
	{
		return randomFloat() * (max*min -1) + min;
	}

	glm::vec2 randomUintVector()
	{
		float angle = TWO_PI * randomFloat();
		return glm::vec2(cos(angle),sin(angle));
	}

	int randomInt()
	{
		return rand();
	}

	int randomIntInRange(int max)
	{
		return rand() % max;
	}
};
#endif