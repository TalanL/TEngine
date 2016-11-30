#include <GL\glew.h>
#include "AStar.h"
AStar AStar::aStarInstance;
AStar& AStar::getAStarInstance()
{
	return aStarInstance;
}

AStar::AStar()
{
}
AStar::~AStar()
{
}

AStar::AStarCost* AStar::CalcAStar(GameNode* start, GameNode* end)
{
	//first node on the list
	AStarCost* nodeCost = new AStarCost();
	nodeCost->refrenceNode = start;
	nodeCost->parent = NULL;
	nodeCost->heuristic = CalcHeuristic(start, end);
	nodeCost->costSoFar = 0;
	nodeCost->totalEstimatedCost = nodeCost->heuristic + nodeCost->costSoFar;
	openList.append(nodeCost);
	//populate open list with connections
	CalcAStarConnections(nodeCost, end);
	return findAStarPath(end);
}

void AStar::CalcAStarConnections(AStarCost* cost, GameNode* end)
{
	for(uint i = 0; i < cost->refrenceNode->numConnections; i++)
	{
		AStarCost* nodeCost = new AStarCost();
		nodeCost->refrenceNode = cost->refrenceNode->connections[i].node;
		nodeCost->parent = cost;
		nodeCost->heuristic = CalcHeuristic(cost->refrenceNode->connections[i].node, end);
		nodeCost->costSoFar = cost->refrenceNode->connections[i].cost + nodeCost->parent->costSoFar;
		nodeCost->totalEstimatedCost = nodeCost->heuristic + nodeCost->costSoFar;
		openList.append(nodeCost);
	}
	closeList.append(cost);
	openList.removeOne(cost);
}

AStar::AStarCost* AStar::findAStarPath(GameNode* end)
{
	AStarCost* path = openList.at(0);
	for(int i = 0; i < openList.size();i++)
	{
		float openCost = openList.at(i)->totalEstimatedCost;
		if(openCost < path->totalEstimatedCost)
		{
			path = openList.at(i);
		}
		//huristic = 0 means you are on the end node. 
	}
	CalcAStarConnections(path, end);
	bool listIsEmpty = openList.isEmpty();
	bool positionSame = path->refrenceNode->postion == end->postion;
	bool connectionSame = path->refrenceNode->connections == end->connections;
	return (!listIsEmpty) ? ((positionSame && connectionSame) ? path : findAStarPath(end)) : NULL;
}


float AStar::CalcHeuristic(GameNode* start, GameNode* end)
{
	return glm::length(start->postion - end->postion);
}

void AStar::clearLists()
{
	for(int i = 0; i < openList.size(); i++)
	{
		delete openList.at(i);

	}
	openList.clear();
	for(int i = 0; i < closeList.size(); i++)
	{
		delete closeList.at(i);
	}
	closeList.clear();
}