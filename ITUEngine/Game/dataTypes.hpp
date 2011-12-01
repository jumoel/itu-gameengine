#pragma once
#include <vector>
class coord 
{ 
public: 
   int x,y; 
}; 

class node 
{ 
public: 
   coord pos; 
   std::vector<coord> parents;
   node* child;
   int distance;
};

class plan
{
public:
	std::vector<node*> openList;
	std::vector<node*> closedList;
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
	WALL,
	COOKIE,
	TELEPORT1,
	TELEPORT2,
	TELEPORT3,
	TELEPORT4,
	TELEPORT5,
	TELEPORT6,
	TELEPORT7,
	TELEPORT8
};