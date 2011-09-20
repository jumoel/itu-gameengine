#include "SceneData.h"

Object* createGraph()
{
	auto root = new Object();

	auto m1 = new Matrix4x4f();

	m1->data[0] = m1->data[1] = m1->data[2] = m1->data[3] = m1->data[4] = m1->data[5] = m1->data[6] = m1->data[7] = m1->data[8] = m1->data[9] = m1->data[10] = m1->data[11] = m1->data[12] = m1->data[13] = m1->data[14] = m1->data[15] = 0;

	m1->data[0] = 1;
	m1->data[5] = 1;
	m1->data[10] = 1;
	m1->data[15] = 1;

	m1->data[3] = 0; // x
	m1->data[7] = 0; // y
	m1->data[11] = -4; // z

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