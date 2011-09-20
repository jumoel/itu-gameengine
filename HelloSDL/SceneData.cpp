#include "SceneData.h"

Object* createGraph()
{
	auto root = new Object();

	auto triangle1 = new Object();

	triangle1->vertices->push_back(*(new Vector3f()));
	triangle1->vertices->push_back(*(new Vector3f(1, 1, 0)));
	triangle1->vertices->push_back(*(new Vector3f(1, 0, 0)));
	
	triangle1->colors->push_back(*(new Vector3f(1, 0, 0)));
	triangle1->colors->push_back(*(new Vector3f(0, 1, 0)));
	triangle1->colors->push_back(*(new Vector3f(0, 0, 1)));

	root->children->push_back(*triangle1);

	return root;
}