#ifndef GAMECONNECTION_H
#define GAMECONNECTION_H
#include "ExportHeader.h"
class GameNode;
class ENGINE_SHARED GameConnection
{
public:
	GameNode* node;
	float cost;
};


#endif