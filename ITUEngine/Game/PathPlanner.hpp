#ifndef ITUENGINE_MEDIA_PATHPLANNER_H
#define ITUENGINE_MEDIA_PATHPLANNER_H

#include <vector>
#include <iostream>
#include <Vector2f.hpp>
#include <Templates/TSingleton.hpp>
#include <Math/GeometricFigures2D.hpp>
#include <Events/Input/KeyPressedEvent.hpp>

class Node 
{ 
public: 
   Vector2f pos; 
   std::vector<Point> parents;
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
	std::vector<Point>* route;
	int targetX;
	int targetY;

	Plan();
	~Plan();

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
	PLAYER,
	TARGET,
};


//#define WEIGHT_DIST 5.0f
//#define MULTIPLIER 100.0f
//#define DANGER_DIST 3.0f

#define MAP_SIZE 40

class PathPlanner : public IKeyboardEvent
{
	SINGLETON( PathPlanner )

public:
	
	std::vector<std::vector<int>> map;
	
	vector<Point> *debugRoute;
	Point playerPos;

	void StartUp(int width);
	void ShutDown();
	void DrawDebug();

	void SetupStaticMap(std::vector<std::vector<int>> *staticMap);

	void UpdateDynamicMap(std::vector<std::vector<int>> *dynamicMap);

	bool isValidNeighbour(Node *neighbour, Plan *plan);

	Node* backTrack(Node *cNode, Plan *plan, int locationX, int locationY);

	Node* recursiveAstar(Node *currentNode, Plan *plan);
	//node* recursiveAstar(node* currentNode, plan* ghostPlan, int weightX, int weightY, std::vector<std::vector<int> > &map);

	std::vector<Point>* aStar(float distinationX, float distinationY, float locationX, float locationY);

	float ConvertToPhysicsMapCoordinates( float x );
	int ConvertToPlanningMapCoordinate( float x );

	//void aStar(int &steps, int &outX, int &outY, int distinationX, int distinationY, int locationX, int locationY, int weightX, int weightY, std::vector<std::vector<int> > &map);
protected:
	void OnKeyDown(KeyPressedEvent *key);
private:

	

	//Number of divisions of the map, for usage in the path planning
	int mapDivisions;

	//Level Width or Height divided by MapDivisions (NOTE: only works for Square levels)
	float mapWidth;
};



#endif