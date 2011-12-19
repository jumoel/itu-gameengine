#pragma once
#include <Game/PathPlanner.hpp>
#include <iostream>
#include <Windows.h>
#include <Managers/InputManager.hpp>

//#define PATH_DEBUG

void PathPlanner::StartUp(int width)
{
	mapDivisions = MAP_SIZE;
	mapWidth = width;
	
	for(int x = 0; x < mapDivisions; x++)
	{
		vector<int> temp;

		for(int y = 0; y < mapDivisions; y++)
		{
			temp.push_back(FREE);
		}
		map.push_back(temp);
	}
}

void PathPlanner::ShutDown()
{
	
}

void PathPlanner::DrawDebug()
{
#ifdef PATH_DEBUG
	system("CLS");

	for(int y = 0; y < mapDivisions; y++)
	{
		for(int x = 0; x < mapDivisions; x++)
		{
			if(map[x][y] == BLOCKED)
			{
				std::cout << "*";
			}
			else if(map[x][y] == FREE)
			{
				std::cout << " ";
			}
			else if(map[x][y] == PLAYER)
			{
				std::cout << "P";
			}
			else if(map[x][y] == TARGET)
			{
				std::cout << "T";
			}
		}
		std::cout << std::endl;
	}
#endif
 }

void PathPlanner::SetupStaticMap(std::vector<std::vector<int>> *staticMap)
{
	for(int x = 0; x < mapDivisions; x++)
	{
		for(int y = 0; y < mapDivisions; y++)
		{
			if(staticMap->at(x).at(y) != FREE)
			{
				map[x][y] = staticMap->at(x).at(y);
			}
		}
	}
}

void PathPlanner::UpdateDynamicMap(std::vector<std::vector<int>> *dynamicMap)
{
	for(int x = 0; x < mapDivisions; x++)
	{
		for(int y = 0; y < mapDivisions; y++)
		{
			if(map[x][y] == PLAYER || map[x][y] == TARGET)
			{
				map[x][y] = FREE;
			}

			if(dynamicMap->at(x).at(y) != FREE)
			{
				map[x][y] = dynamicMap->at(x).at(y);
			}
		}
	}
}

bool PathPlanner::isValidNeighbour(Node* neighbour, Plan* plan)
{
	if((neighbour->pos.y() < 0)
		|| (neighbour->pos.y() > map.size()-1)
		|| (neighbour->pos.x() < 0)
		|| (neighbour->pos.x() > map[neighbour->pos.y()].size()-1))
	{
		return false;
	}
	if(map[neighbour->pos.x()][neighbour->pos.y()] == BLOCKED)
	{
		return false;
	}
	for(int j = 0; j < plan->closedList.size(); j++)
	{
		if((plan->closedList[j]->pos.x() == neighbour->pos.x()) && (plan->closedList[j]->pos.y() == neighbour->pos.y()))
		{
			return false;
		}
	}
	for(int j = 0; j < plan->openList.size(); j++)
	{
		if((plan->openList[j]->pos.x() == neighbour->pos.x()) && (plan->openList[j]->pos.y() == neighbour->pos.y()))
		{
			return false;
		}
	}
	return true;
}

Node* PathPlanner::backTrack(Node* cNode, Plan *plan, int locationX, int locationY)
{
	
 	if(cNode == NULL || cNode->child == NULL)
		return NULL;
	
	plan->route->insert(plan->route->begin(), Point(cNode->pos));
	
	if ((cNode->child->pos.x() == locationX) && (cNode->child->pos.y() == locationY)) 
	{
		return cNode;
	}
	else 
	{
		return backTrack(cNode->child, plan, locationX, locationY);
	}
}

Node* PathPlanner::recursiveAstar(Node* currentNode, Plan* plan)
{
	if((currentNode->pos.x() == plan->targetX) && (currentNode->pos.y() == plan->targetY))
	{
		return currentNode;
	}
	plan->closedList.push_back(currentNode);
	for(int i = 0; i < plan->openList.size(); i++)
	{
		if(currentNode == plan->openList[i])
			plan->openList.erase(plan->openList.begin() + i);
	}
	
	Node* neighbours[8];
	int k = 0;
	for(int i = -1; i <= 1; i++)
	{
		for(int j = -1; j <= 1; j++)
		{
			if(j != 0 || i != 0)
			{
				neighbours[k] = new Node();
				neighbours[k]->pos.SetX(currentNode->pos.x() + i);
				neighbours[k]->pos.SetY(currentNode->pos.y() + j);
				k++;
			}
		}
	}
	
	for(int i = 0; i < 8; i++)
	{
		if(isValidNeighbour(neighbours[i], plan))
		{

			neighbours[i]->steps = currentNode->steps + 1;
			neighbours[i]->distance = neighbours[i]->steps + abs(plan->targetX - neighbours[i]->pos.x()) + abs(plan->targetY - neighbours[i]->pos.y());
			neighbours[i]->child = currentNode;
			plan->openList.push_back(neighbours[i]);
		}
		else 
		{
			delete neighbours[i];
		}
	}
	
	if(plan->openList.size() < 1)
		return NULL;
		
	currentNode = plan->openList[0];

	for(int i = 1; i < plan->openList.size(); i++)
	{
		if(plan->openList[i]->distance < currentNode->distance)
			currentNode = plan->openList[i];
	}
	
	return recursiveAstar(currentNode, plan); 
}

bool PathPlanner::evaluateCoordinate(float *x, float *y)
{
	if(*x >= mapDivisions)
	{
		*x = mapDivisions-1;
	}
	else if(*x < 0)
	{
		*x = 0;
	}
	if(*y >= mapDivisions)
	{
		*y = mapDivisions-1;
	}
	else if(*y < 0)
	{
		*y = 0;
	}
	bool result = true;
	if(map[*x][*y] == BLOCKED)
	{
		result = checkForFreeSpaces(x, y, 1);
	}

	return result;
}

bool PathPlanner::checkForFreeSpaces(float *x, float *y, int i)
{
	if(0 > *x-i && *x+i > mapDivisions-1 && 0 > *y-i && *y+i > mapDivisions-1)
	{
		return false;
	}
	std::vector<Vector2f> tempList;
	for(int j = -i; j < i; j++)
	{
		for(int k = -i; k < i; k++)
		{
			if(j == -i || j == i || k == -i || k == i)
			{
				if(0 < *x+j  && *x+j < mapDivisions-1 && 0 < *y+k && *y+k < mapDivisions-1)
				{
					if(map[*x+j][*y+k] != BLOCKED)
					{
						tempList.push_back(Vector2f(j,k));
					}
				}
			}
		}
	}
	bool result = true;
	if(tempList.size() > 0)
	{
		float shortestDist = 9999.9f;
		int shortestIndex = 0;
		for(unsigned int index = 0; index < tempList.size(); index++)
		{
			float dist = tempList.at(index).x()*tempList.at(index).x() + tempList.at(index).y()*tempList.at(index).y();
			if(dist < shortestDist)
			{
				shortestDist = dist;
				shortestIndex = index;
			}
		}
		*x += tempList.at(shortestIndex).x();
		*y += tempList.at(shortestIndex).y();
		result = true;
	}
	else
	{
		result = checkForFreeSpaces(x, y, i+1);
	}
	return result;
}

std::vector<Point>* PathPlanner::aStar(float distinationX, float distinationY, float locationX, float locationY)
{
	//Convert to divided map, for planning
	int destX = ConvertToPlanningMapCoordinate(distinationX);
	int destY = ConvertToPlanningMapCoordinate(distinationY);
	int loctX = ConvertToPlanningMapCoordinate(locationX);
	int loctY = ConvertToPlanningMapCoordinate(locationY);

	//Planning
	Plan plan;
	
	plan.targetX = destX;
	plan.targetY = destY;
	Node* currentNode = new Node();
	currentNode->pos.SetX(loctX);
	currentNode->pos.SetY(loctY);
	currentNode->child = NULL;
	currentNode->steps = 0;
	currentNode->distance = abs(destX - currentNode->pos.x()) + abs(destY - currentNode->pos.y());
	backTrack(recursiveAstar(currentNode, &plan), &plan, loctX, loctY);
	plan.clear();
	
	std::vector<Point>::iterator planRouteIterator;

	for(planRouteIterator = plan.route->begin(); 
		planRouteIterator != plan.route->end();
		planRouteIterator++)
	{
		planRouteIterator->X = ConvertToPhysicsMapCoordinates(planRouteIterator->X);
		planRouteIterator->Y = ConvertToPhysicsMapCoordinates(planRouteIterator->Y);
	}
	
	return plan.route;
}

int PathPlanner::ConvertToPlanningMapCoordinate( float x )
{
	return (int) ((x / mapWidth) * mapDivisions);
}

float PathPlanner::ConvertToPhysicsMapCoordinates( float x )
{
	return (mapWidth / mapDivisions) * x + (mapWidth / mapDivisions)*0.5f;
}

Plan::Plan()
{
	route = new vector<Point>();
}

Plan::~Plan()
{

}
