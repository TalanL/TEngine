#ifndef ASTAR_H
#define ASTAR_H
#include "glm.hpp"
#include "Qt\qlist.h"
#include "GameNode.h"
#include "ExportHeader.h"
class ENGINE_SHARED AStar
{
	AStar(const AStar&);
	AStar& operator = (const AStar&);
	static AStar aStarInstance; 
public:
	static AStar& getAStarInstance();
	AStar();
	~AStar();

	struct AStarCost
	{
		GameNode* refrenceNode;
		AStarCost* parent;
		float costSoFar;
		float totalEstimatedCost;
		float heuristic;
	};

	QList<AStarCost*> openList;
	QList<AStarCost*> closeList;
	AStarCost* processingNode;
	AStarCost* CalcAStar(GameNode* start, GameNode* end);
	AStarCost* findAStarPath(GameNode* end);
	void clearLists();
	void CalcAStarConnections(AStarCost* cost, GameNode* end);
	float CalcHeuristic(GameNode* start, GameNode* end);
};

#define aStar AStar::getAStarInstance()
#endif