#pragma once
#include <Game/dataTypes.hpp>
#include "math.h"
#include <iostream>

using namespace std;

#define WEIGHT_DIST 5.0f
#define MULTIPLIER 100.0f
#define DANGER_DIST 3.0f

bool isValidNeighbour(node* neighbour, plan* ghostPlan, std::vector<std::vector<int> > &map);

node* backTrack(int &steps, node* cNode, int locationX, int locationY);

node* recursiveAstar(node* currentNode, plan* ghostPlan, std::vector<std::vector<int> > &map);
node* recursiveAstar(node* currentNode, plan* ghostPlan, int weightX, int weightY, std::vector<std::vector<int> > &map);

void aStar(int &steps, int &outX, int &outY, int distinationX, int distinationY, int locationX, int locationY, std::vector<std::vector<int> > &map);
void aStar(int &steps, int &outX, int &outY, int distinationX, int distinationY, int locationX, int locationY, int weightX, int weightY, std::vector<std::vector<int> > &map);