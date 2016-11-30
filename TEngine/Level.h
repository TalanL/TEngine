#ifndef LEVEL_H
#define LEVEL_H
#include "Render\GeometryInfo.h"
#include "AI\AStar\GameNode.h"
class Level
{
public:
	Level();
	~Level();
	int numNodes;
	GameNode* nodes;
	GeometryInfo* levelGeo;
};

#endif