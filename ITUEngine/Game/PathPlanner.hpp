#ifndef ITUENGINE_MEDIA_PATHPLANNER_H
#define ITUENGINE_MEDIA_PATHPLANNER_H

#include "math.h"
#include <vector>
#include <iostream>
#include <Vector2f.hpp>
#include <Templates/TSingleton.hpp>
#include <Managers/SceneGraphManager.hpp>

class Node 
{ 
public: 
   Vector2f pos; 
   std::vector<Vector2f> parents;
   Node* child;
   int distance;
   int steps;

   Node(){steps = 0;};
};

class Plan
{
public:
	std::vector<Node*> openList;
	std::vector<Node*> closedList;
	std::vector<Vector2f> route;
	int targetX;
	int targetY;

	void clear()
	{
		for(int i = 0; i < openList.size(); i++)
		{
			delete openList[i];
		}
		for(int i = 0; i < closedList.size(); i++)
		{
			delete closedList[i];
		}
		openList.clear();
		closedList.clear();
	}
};

enum gridElements
{
	FREE,
	BLOCKED,
};


//#define WEIGHT_DIST 5.0f
//#define MULTIPLIER 100.0f
//#define DANGER_DIST 3.0f

class PathPlanner
{
	SINGLETON( PathPlanner )

public:
	
	std::vector<std::vector<int> > map;
	SceneGraphManager *m_SceneGraph;

	void StartUp(SceneGraphManager *graph);
	void ShutDown();

	void UpdateMap();

	bool isValidNeighbour(Node* neighbour, Plan* plan);

	Node* backTrack(Node* cNode, Plan *plan, int locationX, int locationY);

	Node* recursiveAstar(Node* currentNode, Plan* plan);
	//node* recursiveAstar(node* currentNode, plan* ghostPlan, int weightX, int weightY, std::vector<std::vector<int> > &map);

	std::vector<Vector2f> aStar(int distinationX, int distinationY, int locationX, int locationY);
	//void aStar(int &steps, int &outX, int &outY, int distinationX, int distinationY, int locationX, int locationY, int weightX, int weightY, std::vector<std::vector<int> > &map);
	
};



#endif