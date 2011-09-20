#include "SceneData.h"
#include "Camera.h"

Object* createGraph()
{
	auto root = new Object();
	root->Name = "Root";

	auto camera = new Camera();
	camera->Position = new Vector3f(0, 0, 0);
	camera->Up = new Vector3f(0, 1, 0);
	camera->LookAt = new Vector3f(0, 0, 1);
	camera->Name = "Camera";

	root->children->push_back(*camera);

	auto triangle1 = new Object();
	triangle1->Name = "T1";
	
	triangle1->transformation = (new Matrix4x4f())->Translate(0, 0, -6);

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

	auto triangle2 = new Object();
	triangle2->Name = "T2";

	triangle2->vertices->push_back(*v1);
	triangle2->vertices->push_back(*v2);
	triangle2->vertices->push_back(*v3);
	
	triangle2->colors->push_back(*c1);
	triangle2->colors->push_back(*c1);
	triangle2->colors->push_back(*c1);
	triangle2->transformation = (new Matrix4x4f())->Translate(2, 0.5, -4);

	triangle1->children->push_back(*triangle2);

	auto triangle3 = new Object();
	triangle3->Name = "T3";

	triangle3->vertices->push_back(*v1);
	triangle3->vertices->push_back(*v2);
	triangle3->vertices->push_back(*v3);
	
	triangle3->colors->push_back(*c2);
	triangle3->colors->push_back(*c2);
	triangle3->colors->push_back(*c2);
	triangle3->transformation = (new Matrix4x4f())->Translate(-2, -0.5, -4);

	triangle1->children->push_back(*triangle2);
	triangle1->children->push_back(*triangle3);

	root->children->push_back(*triangle1);

	return root;
}