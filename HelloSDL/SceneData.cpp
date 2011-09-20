#include "SceneData.h"

Object* createGraph()
{
	auto root = new Object();

	auto m1 = new Matrix4x4f();
	m1->Translate(0, 0, -10);
	root->transformation = m1;

	auto triangle1 = new Object();
	auto v1 = new Vector3f(0, 0, 0);
	auto v2 = new Vector3f(1, 1, 0);
	auto v3 = new Vector3f(1, 0, 0);
	
	auto c1 = new Vector3f(1, 0, 0);
	auto c2 = new Vector3f(0, 1, 0);
	auto c3 = new Vector3f(0, 0, 1);

	triangle1->vertices->push_back(*v1);
	triangle1->vertices->push_back(*v2);
	triangle1->vertices->push_back(*v3);
	
	triangle1->colors->push_back(*c1);
	triangle1->colors->push_back(*c2);
	triangle1->colors->push_back(*c3);

	root->children->push_back(*triangle1);

	return root;
}