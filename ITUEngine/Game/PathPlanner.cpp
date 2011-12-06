#pragma once
#include <Game/PathPlanner.hpp>
#include <iostream>
#include <Windows.h>
#include <Managers\InputManager.hpp>

#define MAP_SIZE 20

#define PATH_DEBUG

void PathPlanner::StartUp()//SceneGraphManager *graph)
{
	mapDivisions = MAP_SIZE;

	//TODO: initialize probably
	mapWidth = 20;

	InputManager::RegisterKeyboardEventHandler(this);
	//m_SceneGraph = graph;
	playerPos.X = 5;
	playerPos.Y = 5;


	for(int x = 0; x < mapDivisions; x++)
	{
		vector<int> temp;
		
		for(int y = 0; y < mapDivisions; y++)
		{
			
			if(x == 0 || y == 0 || x == mapDivisions-1 || y == mapDivisions-1)
			{
				temp.push_back(BLOCKED);
			}
			else if(x == playerPos.X && y == playerPos.Y)
			{
				temp.push_back(PLAYER);
			}
			else
			{
				temp.push_back(FREE);
			}
		}
		map.push_back(temp);
	}

	map[6][1] = BLOCKED;
	map[6][2] = BLOCKED;
	map[6][3] = BLOCKED;
	map[6][4] = BLOCKED;
	map[6][5] = BLOCKED;
	map[6][6] = BLOCKED;
	map[6][7] = BLOCKED;
	map[6][8] = BLOCKED;
	map[6][9] = BLOCKED;
	map[6][10] = BLOCKED;
	map[5][10] = BLOCKED;
	map[4][10] = BLOCKED;
	map[4][9] = BLOCKED;
	map[4][8] = BLOCKED;
	map[4][7] = BLOCKED;
	map[4][6] = BLOCKED;
	map[4][5] = BLOCKED;
	map[4][4] = BLOCKED;
	map[4][3] = BLOCKED;
	map[4][2] = BLOCKED;

	map[7][5] = TARGET;
	debugRoute = aStar(7.0f, 5.0f, playerPos.X, playerPos.Y);
	std::cout << "route size: " << debugRoute->size() << std::endl;
	//UpdateMap();
}

void PathPlanner::ShutDown()
{
	
}

void PathPlanner::Run()
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

void PathPlanner::OnKeyDown(KeyPressedEvent *key)
{
	auto keyInput = key->GetInput();

	switch(keyInput->keysym.sym)
	{
		case SDLK_b:
			UpdateMap();
			break;
	}
}

void PathPlanner::UpdateMap()
{
	if(debugRoute->size() > 0)
	{
		map[playerPos.X][playerPos.Y] = FREE;
		playerPos.X = debugRoute->at(0).X;
		playerPos.Y = debugRoute->at(0).Y;
		debugRoute->erase(debugRoute->begin());
		map[playerPos.X][playerPos.Y] = PLAYER;
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
	
 	if(cNode->child == NULL)
		return NULL;
	
	plan->route->insert(plan->route->begin(), Point(cNode->pos));
	
	if ((cNode->child->pos.x() == locationX) && (cNode->child->pos.y() == locationY)) {
		//route.push_back(cNode);
		//return;
		//cout << endl;
		//cout << endl;
		return cNode;
	}
	else {
		//cout << "(" << cNode->pos.x << "," << cNode->pos.y << ")->";
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

std::vector<Point>* PathPlanner::aStar(float distinationX, float distinationY, float locationX, float locationY)
{
	//Convert to divided map, for planning
	auto destX = ConvertToPlanningMapCoordinate(distinationX);
	auto destY = ConvertToPlanningMapCoordinate(distinationY);
	auto loctX = ConvertToPlanningMapCoordinate(locationX);
	auto loctY = ConvertToPlanningMapCoordinate(locationY);

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
	return (mapWidth/mapDivisions) * x;
}

#if 0
node* recursiveAstar(node* currentNode, plan* ghostPlan, int weightX, int weightY, std::vector<std::vector<int> > &map)
{
	if((currentNode->pos.x() == ghostPlan->targetX) && (currentNode->pos.y() == ghostPlan->targetY))
	{
		return currentNode;
	}
	ghostPlan->closedList.push_back(currentNode);
	for(int i = 0; i < ghostPlan->openList.size(); i++)
	{
		if(currentNode == ghostPlan->openList[i])
			ghostPlan->openList.erase(ghostPlan->openList.begin() + i);
	}
	
	//vector<node*> neighbours;
	node* neighbours[4];
	for(int i = 0; i < 4; i++)
	{
		neighbours[i] = new node();
	}
	neighbours[0]->pos.SetX(currentNode->pos.x()-1);
	neighbours[0]->pos.SetY(currentNode->pos.y());
	neighbours[1]->pos.SetX(currentNode->pos.x()+1);
	neighbours[1]->pos.SetY(currentNode->pos.y());
	neighbours[2]->pos.SetX(currentNode->pos.x());
	neighbours[2]->pos.SetY(currentNode->pos.y()-1);
	neighbours[3]->pos.SetX(currentNode->pos.x());
	neighbours[3]->pos.SetY(currentNode->pos.y()+1);

	for(int i = 0; i < 4; i++)
	{
		if(isValidNeighbour(neighbours[i], ghostPlan, map))
		{
			float weightDist = sqrt((float)((weightX - currentNode->pos.x())*(weightX - currentNode->pos.x()) + (weightY - currentNode->pos.y())*(weightY - currentNode->pos.y())));
			if(weightDist < WEIGHT_DIST)
			{
				/*if(weightDist < DANGER_DIST)
				{
					weightDist = 9999.0f;
				}
				else
				{*/
					weightDist = (1 - (weightDist/WEIGHT_DIST))*MULTIPLIER;
				//}
				
			}
			else
				weightDist = 0;

			neighbours[i]->distance = abs(ghostPlan->targetX - currentNode->pos.x()) + abs(ghostPlan->targetY - currentNode->pos.y()) + weightDist;
			neighbours[i]->child = currentNode;
			ghostPlan->openList.push_back(neighbours[i]);
		}
		else 
		{
			/*node* temp = neighbours[i]
			neighbours.erase(neighbours.begin() + i);
			delete temp;
			*/
			delete neighbours[i];
		}
	}
	//neighbours.clear();
	
	if(ghostPlan->openList.size() < 1)
		return NULL;
		
	currentNode = ghostPlan->openList[0];

	for(int i = 1; i < ghostPlan->openList.size(); i++)
	{
		if(ghostPlan->openList[i]->distance < currentNode->distance)
			currentNode = ghostPlan->openList[i];
	}
	
	return recursiveAstar(currentNode, ghostPlan, weightX, weightY, map); 
}

void aStar(int &steps, int &outX, int &outY, int distinationX, int distinationY, int locationX, int locationY, int weightX, int weightY, std::vector<std::vector<int> > &map)
{
	plan ghostPlan;
	ghostPlan.targetX = distinationX;
	ghostPlan.targetY = distinationY;
	node* currentNode = new node();
	currentNode->pos.SetX(locationX);
	currentNode->pos.SetY(locationY);
	currentNode->child = NULL;
	currentNode->distance = abs(distinationX - currentNode->pos.x()) + abs(distinationX - currentNode->pos.y());
	node* finalNode = backTrack(steps, recursiveAstar(currentNode, &ghostPlan, weightX, weightY, map), locationX, locationY);
	if(finalNode != NULL)
	{
		outX = finalNode->pos.x();
		outY = finalNode->pos.y();
	}
	else
	{
		outX = -1;
		outY = -1;
	}
	ghostPlan.clear();
}
#endif

Plan::Plan()
{
	route = new vector<Point>();
}

Plan::~Plan()
{

}
