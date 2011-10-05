#include "SceneData.h"
#include "Camera.h"
#include "../Managers/SceneGraphManager.h"
#include "../Managers/MediaManager.h"

SceneGraphManager *createGraph()
{
	auto root = new Object();
	root->Name = "Root";

	auto triangle1 = new Object();
	triangle1->Name = "T1";

	auto m = new Matrix4x4f();
	m->Translate(0.0f, 0.0f, -4.0f);
	
	triangle1->transformation = m;

	auto v1 = new Vector3f(-0.5f, -0.5f, 0.0f);
	auto v2 = new Vector3f(0.0f, 0.5f, 0.0f);
	auto v3 = new Vector3f(0.5f, -0.5f, 0.0f);
	
	auto c1 = new Vector3f(1, 0, 0);
	auto c2 = new Vector3f(0, 1, 0);
	auto c3 = new Vector3f(0, 0, 1);

	auto uv1 = new TexCoord(0.0f , 0.0f);
	auto uv2 = new TexCoord(0.0f , 1.0f);
	auto uv3 = new TexCoord(1.0f , 1.0f);

	triangle1->gfx->vertices->push_back(*v1);
	triangle1->gfx->vertices->push_back(*v2);
	triangle1->gfx->vertices->push_back(*v3);
	
	triangle1->gfx->colors->push_back(*c1);
	triangle1->gfx->colors->push_back(*c2);
	triangle1->gfx->colors->push_back(*c3);

	triangle1->gfx->uv->push_back(*uv1);
	triangle1->gfx->uv->push_back(*uv2);
	triangle1->gfx->uv->push_back(*uv3);

	triangle1->gfx->texture = SINGLETONINSTANCE(MediaManager)->warrior;
	
	auto triangle2 = new Object();
	triangle2->Name = "T2";

	triangle2->gfx->vertices->push_back(*v1);
	triangle2->gfx->vertices->push_back(*v2);
	triangle2->gfx->vertices->push_back(*v3);
	
	triangle2->gfx->colors->push_back(*c1);
	triangle2->gfx->colors->push_back(*c1);
	triangle2->gfx->colors->push_back(*c1);

	triangle2->gfx->uv->push_back(*uv1);
	triangle2->gfx->uv->push_back(*uv2);
	triangle2->gfx->uv->push_back(*uv3);

	triangle2->gfx->texture = SINGLETONINSTANCE(MediaManager)->warrior;

	triangle2->transformation = (new Matrix4x4f())->Translate(0, 0, -4.0f);

	triangle1->children->push_back(*triangle2);

	auto triangle3 = new Object();
	triangle3->Name = "T3";

	triangle3->gfx->vertices->push_back(*v1);
	triangle3->gfx->vertices->push_back(*v2);
	triangle3->gfx->vertices->push_back(*v3);
	
	triangle3->gfx->colors->push_back(*c2);
	triangle3->gfx->colors->push_back(*c2);
	triangle3->gfx->colors->push_back(*c2);

	triangle3->gfx->uv->push_back(*uv1);
	triangle3->gfx->uv->push_back(*uv2);
	triangle3->gfx->uv->push_back(*uv3);

	triangle3->gfx->texture = SINGLETONINSTANCE(MediaManager)->warrior;

	triangle3->transformation = (new Matrix4x4f())->Translate(-2, 0, 0);

	triangle1->children->push_back(*triangle3);
	
	root->children->push_back(*triangle1);

	auto camera = new Camera();
	camera->Position = *(new Vector3f(0, 0, 0));
	camera->LookAt = *(new Vector3f(0, 0, -1));
	camera->Up = *(new Vector3f(0, 1, 0));
	//camera->Up = *(new Vector3f(1, 1, 0));

	return new SceneGraphManager(camera, root);
}

SceneGraphManager *createGraphVBO()
{
	auto root = new Object();
	root->Name = "Root";

	auto triangle1 = new Object();
	triangle1->Name = "T1";

	auto m = new Matrix4x4f();
	m->Translate(0.0f, 0.0f, -10.0f);
	
	triangle1->transformation = m;

	auto v1 = new Vector3f(-0.5f, -0.5f, 0.0f);
	auto v2 = new Vector3f(0.0f, 0.5f, 0.0f);
	auto v3 = new Vector3f(0.5f, -0.5f, 0.0f);
	
	auto c1 = new Vector3f(1, 0, 0);
	auto c2 = new Vector3f(0, 1, 0);
	auto c3 = new Vector3f(0, 0, 1);

	auto uv1 = new TexCoord(0.0f , 0.0f);
	auto uv2 = new TexCoord(0.0f , 1.0f);
	auto uv3 = new TexCoord(1.0f , 1.0f);

	triangle1->gfx->vertices->push_back(*v1);
	triangle1->gfx->vertices->push_back(*v2);
	triangle1->gfx->vertices->push_back(*v3);
	
	triangle1->gfx->colors->push_back(*c1);
	triangle1->gfx->colors->push_back(*c2);
	triangle1->gfx->colors->push_back(*c3);

	triangle1->gfx->uv->push_back(*uv1);
	triangle1->gfx->uv->push_back(*uv2);
	triangle1->gfx->uv->push_back(*uv3);

	//triangle1->gfx->spec = 0.5f;
	triangle1->gfx->shine = 0.3f;
	triangle1->gfx->texture = SINGLETONINSTANCE(MediaManager)->warrior;
	
	triangle1->gfx->CreateVBO();

	auto triangle2 = new Object();
	triangle2->Name = "T2";

	triangle2->gfx->vertices->push_back(*v1);
	triangle2->gfx->vertices->push_back(*v2);
	triangle2->gfx->vertices->push_back(*v3);
	
	triangle2->gfx->colors->push_back(*c1);
	triangle2->gfx->colors->push_back(*c1);
	triangle2->gfx->colors->push_back(*c1);

	triangle2->gfx->uv->push_back(*uv1);
	triangle2->gfx->uv->push_back(*uv2);
	triangle2->gfx->uv->push_back(*uv3);

	//triangle2->gfx->spec = 0.5f;
	triangle2->gfx->shine = 0.3f;
	triangle2->gfx->texture = SINGLETONINSTANCE(MediaManager)->warrior;

	triangle2->transformation = (new Matrix4x4f())->Translate(0, 0, -4.0f);

	triangle2->gfx->CreateVBO();

	triangle1->children->push_back(*triangle2);

	auto triangle3 = new Object();
	triangle3->Name = "T3";

	triangle3->gfx->vertices->push_back(*v1);
	triangle3->gfx->vertices->push_back(*v2);
	triangle3->gfx->vertices->push_back(*v3);
	
	triangle3->gfx->colors->push_back(*c2);
	triangle3->gfx->colors->push_back(*c2);
	triangle3->gfx->colors->push_back(*c2);

	triangle3->gfx->uv->push_back(*uv1);
	triangle3->gfx->uv->push_back(*uv2);
	triangle3->gfx->uv->push_back(*uv3);

	//triangle3->gfx->spec = 0.5f;
	triangle3->gfx->shine = 0.3f;
	triangle3->gfx->texture = SINGLETONINSTANCE(MediaManager)->warrior;

	triangle3->transformation = (new Matrix4x4f())->Translate(-2, 0, 0);

	triangle3->gfx->CreateVBO();

	triangle1->children->push_back(*triangle3);
	
	root->children->push_back(*triangle1);

	auto camera = new Camera();
	camera->Position = *(new Vector3f(0, 0, 0));
	camera->LookAt = *(new Vector3f(0, 0, -1));
	camera->Up = *(new Vector3f(0, 1, 0));
	//camera->Up = *(new Vector3f(1, 1, 0));

	

	return new SceneGraphManager(camera, root);
}

void deleteGraphVBO(Object *root)
{
	glDeleteBuffersARB(1, &(root->gfx->vboId));
	glDeleteBuffersARB(1, &(root->gfx->cboId));

	if(root->children->size() < 0)
	{
		auto child_iter = root->children->begin();
		int i = 0;
		while (child_iter != root->children->end())
		{
			deleteGraphVBO(&(*child_iter));
			child_iter++;
		}
	}

}