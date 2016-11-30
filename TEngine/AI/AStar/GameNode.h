#ifndef GAMENODE_H
#define GAMENODE_H
#include "glm.hpp"
#include "GameConnection.h"
#include "ExportHeader.h"
using glm::vec3;

class ENGINE_SHARED GameNode
{
public:
	vec3 postion;
	unsigned int numConnections;
	GameConnection* connections;
};

#endif