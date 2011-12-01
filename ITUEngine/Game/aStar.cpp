#pragma once
#include <Game/aStar.hpp>

bool isValidNeighbour(node* neighbour, plan* ghostPlan, std::vector<std::vector<int> > &map)
{
	if((neighbour->pos.y < 0)
		|| (neighbour->pos.y > map.size()-1)
		|| (neighbour->pos.x < 0)
		|| (neighbour->pos.x > map[neighbour->pos.y].size()-1))
	{
		return false;
	}
	if(map[neighbour->pos.y][neighbour->pos.x] == WALL)
	{
		return false;
	}
	for(int j = 0; j < ghostPlan->closedList.size(); j++)
	{
		if((ghostPlan->closedList[j]->pos.x == neighbour->pos.x) && (ghostPlan->closedList[j]->pos.y == neighbour->pos.y))
		{
			return false;
		}
	}
	for(int j = 0; j < ghostPlan->openList.size(); j++)
	{
		if((ghostPlan->openList[j]->pos.x == neighbour->pos.x) && (ghostPlan->openList[j]->pos.y == neighbour->pos.y))
		{
			return false;
		}
	}
	return true;
}

node* backTrack(int &steps, node* cNode, int locationX, int locationY)
{
 	if(cNode->child == NULL)
		return NULL;

	if ((cNode->child->pos.x == locationX) && (cNode->child->pos.y == locationY)) {
		//route.push_back(cNode);
		//return;
		//cout << endl;
		//cout << endl;
		return cNode;
	}
	else {
		steps++;
		//route.push_back(cNode);
		//backTrack(cNode->child);
		//cout << "(" << cNode->pos.x << "," << cNode->pos.y << ")->";
		return backTrack(steps, cNode->child, locationX, locationY);
	}
}

node* recursiveAstar(node* currentNode, plan* ghostPlan, std::vector<std::vector<int> > &map)
{
	if((currentNode->pos.x == ghostPlan->targetX) && (currentNode->pos.y == ghostPlan->targetY))
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
	neighbours[0]->pos.x = currentNode->pos.x-1;
	neighbours[0]->pos.y = currentNode->pos.y;
	neighbours[1]->pos.x = currentNode->pos.x+1;
	neighbours[1]->pos.y = currentNode->pos.y;
	neighbours[2]->pos.x = currentNode->pos.x;
	neighbours[2]->pos.y = currentNode->pos.y-1;
	neighbours[3]->pos.x = currentNode->pos.x;
	neighbours[3]->pos.y = currentNode->pos.y+1;

	for(int i = 0; i < 4; i++)
	{
		if(isValidNeighbour(neighbours[i], ghostPlan, map))
		{
			neighbours[i]->distance = abs(ghostPlan->targetX - currentNode->pos.x) + abs(ghostPlan->targetY - currentNode->pos.y);
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
	
	return recursiveAstar(currentNode, ghostPlan, map); 
}

void aStar(int &steps, int &outX, int &outY, int distinationX, int distinationY, int locationX, int locationY, std::vector<std::vector<int> > &map)
{
	plan ghostPlan;
	ghostPlan.targetX = distinationX;
	ghostPlan.targetY = distinationY;
	node* currentNode = new node();
	currentNode->pos.x = locationX;
	currentNode->pos.y = locationY;
	currentNode->child = NULL;
	currentNode->distance = abs(distinationX - currentNode->pos.x) + abs(distinationX - currentNode->pos.y);
	node* finalNode = backTrack(steps, recursiveAstar(currentNode, &ghostPlan, map), locationX, locationY);
	if(finalNode != NULL)
	{
		outX = finalNode->pos.x;
		outY = finalNode->pos.y;
	}
	else
	{
		outX = -1;
		outY = -1;
	}
	ghostPlan.clear();
}

node* recursiveAstar(node* currentNode, plan* ghostPlan, int weightX, int weightY, std::vector<std::vector<int> > &map)
{
	if((currentNode->pos.x == ghostPlan->targetX) && (currentNode->pos.y == ghostPlan->targetY))
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
	neighbours[0]->pos.x = currentNode->pos.x-1;
	neighbours[0]->pos.y = currentNode->pos.y;
	neighbours[1]->pos.x = currentNode->pos.x+1;
	neighbours[1]->pos.y = currentNode->pos.y;
	neighbours[2]->pos.x = currentNode->pos.x;
	neighbours[2]->pos.y = currentNode->pos.y-1;
	neighbours[3]->pos.x = currentNode->pos.x;
	neighbours[3]->pos.y = currentNode->pos.y+1;

	for(int i = 0; i < 4; i++)
	{
		if(isValidNeighbour(neighbours[i], ghostPlan, map))
		{
			float weightDist = sqrt((float)((weightX - currentNode->pos.x)*(weightX - currentNode->pos.x) + (weightY - currentNode->pos.y)*(weightY - currentNode->pos.y)));
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

			neighbours[i]->distance = abs(ghostPlan->targetX - currentNode->pos.x) + abs(ghostPlan->targetY - currentNode->pos.y) + weightDist;
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
	currentNode->pos.x = locationX;
	currentNode->pos.y = locationY;
	currentNode->child = NULL;
	currentNode->distance = abs(distinationX - currentNode->pos.x) + abs(distinationX - currentNode->pos.y);
	node* finalNode = backTrack(steps, recursiveAstar(currentNode, &ghostPlan, weightX, weightY, map), locationX, locationY);
	if(finalNode != NULL)
	{
		outX = finalNode->pos.x;
		outY = finalNode->pos.y;
	}
	else
	{
		outX = -1;
		outY = -1;
	}
	ghostPlan.clear();
}
