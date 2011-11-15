#include <Game/SceneData.hpp>
#include <Game/Camera.hpp>
#include <Managers/SceneGraphManager.hpp>
#include <Managers/MediaManager.hpp>
#include <Managers/LightingManager.hpp>

SceneGraphManager *createGraph()
{
	int lightIndex = SINGLETONINSTANCE(LightingManager)->getAvailableLightIndex();
	SINGLETONINSTANCE(LightingManager)->lights[lightIndex].enable(true);
	SINGLETONINSTANCE(LightingManager)->lights[lightIndex].setDiffuse(0.5f,0.5f,0.5f, 1.0f);
	SINGLETONINSTANCE(LightingManager)->lights[lightIndex].setSpecular(0.7f,0.2f,0.1f, 1.0f);
	SINGLETONINSTANCE(LightingManager)->lights[lightIndex].setAmbient(0.2f,0.2f,0.2f, 1.0f);
	SINGLETONINSTANCE(LightingManager)->lights[lightIndex].setPos(0.0f,0.0f,0.0f);

	auto root = new Object();
	root->Name = "Root";

	auto player = new Object();
	player->Name = "Player";
	player->gfx = SINGLETONINSTANCE( MediaManager )->playerModel;
	std::cout << "num of vertices: " << player->gfx->numVertices << std::endl;
	for(int i = 0; i < player->gfx->numMaterials; i++)
	{
		player->gfx->SetTexture(SINGLETONINSTANCE( MediaManager )->playerTex, &player->gfx->mMaterials[i]);
	}

	auto m = new Matrix4x4f();
	m->Translate(0.0f, 0.0f, -4.0f);
	
	root->children->push_back(*player);


	auto camera = new Camera();
	camera->Position.SetX(0);
	camera->Position.SetY(0);
	camera->Position.SetZ(100);
	//camera->MoveCamera3D(new Vector3f(0, 0, 100));
	camera->LookAt.SetX(0);
	camera->LookAt.SetY(0);
	camera->LookAt.SetZ(-1);
	camera->Up.SetX(0);
	camera->Up.SetY(1);
	camera->Up.SetZ(0);
	//camera->Up = *(new Vector3f(1, 1, 0));

	return new SceneGraphManager(camera, root);
}
/*
SceneGraphManager *createGraphVBO()
{

	int lightIndex = SINGLETONINSTANCE(LightingManager)->getAvailableLightIndex();
	SINGLETONINSTANCE(LightingManager)->lights[lightIndex].enable(true);
	SINGLETONINSTANCE(LightingManager)->lights[lightIndex].setDiffuse(0.5f,0.5f,0.5f, 1.0f);
	SINGLETONINSTANCE(LightingManager)->lights[lightIndex].setSpecular(0.7f,0.2f,0.1f, 1.0f);
	SINGLETONINSTANCE(LightingManager)->lights[lightIndex].setAmbient(0.2f,0.2f,0.2f, 1.0f);
	SINGLETONINSTANCE(LightingManager)->lights[lightIndex].setPos(0.0f,0.0f,0.0f);

	auto root = new Object();
	root->Name = "Root";

	float specReflection[] = { 0.8f, 0.8f, 0.8f, 1.0f };

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
	
	triangle1->gfx->material->colors->push_back(*c1);
	triangle1->gfx->material->colors->push_back(*c2);
	triangle1->gfx->material->colors->push_back(*c3);

	triangle1->gfx->material->uv->push_back(*uv1);
	triangle1->gfx->material->uv->push_back(*uv2);
	triangle1->gfx->material->uv->push_back(*uv3);

	triangle1->gfx->material->spec = specReflection;
	triangle1->gfx->material->shine = 0.3f;
	triangle1->gfx->material->texture = SINGLETONINSTANCE(MediaManager)->warrior;
	
	triangle1->gfx->CreateVBO();

	auto triangle2 = new Object();
	triangle2->Name = "T2";

	triangle2->gfx->vertices->push_back(*v1);
	triangle2->gfx->vertices->push_back(*v2);
	triangle2->gfx->vertices->push_back(*v3);
	
	triangle2->gfx->material->colors->push_back(*c1);
	triangle2->gfx->material->colors->push_back(*c1);
	triangle2->gfx->material->colors->push_back(*c1);

	triangle2->gfx->material->uv->push_back(*uv1);
	triangle2->gfx->material->uv->push_back(*uv2);
	triangle2->gfx->material->uv->push_back(*uv3);

	triangle2->gfx->material->spec = specReflection;
	triangle2->gfx->material->shine = 0.3f;
	triangle2->gfx->material->texture = SINGLETONINSTANCE(MediaManager)->warrior;

	triangle2->transformation = (new Matrix4x4f())->Translate(0, 0, -4.0f);

	triangle2->gfx->CreateVBO();

	triangle1->children->push_back(*triangle2);

	auto triangle3 = new Object();
	triangle3->Name = "T3";

	triangle3->gfx->vertices->push_back(*v1);
	triangle3->gfx->vertices->push_back(*v2);
	triangle3->gfx->vertices->push_back(*v3);
	
	triangle3->gfx->material->colors->push_back(*c2);
	triangle3->gfx->material->colors->push_back(*c2);
	triangle3->gfx->material->colors->push_back(*c2);

	triangle3->gfx->material->uv->push_back(*uv1);
	triangle3->gfx->material->uv->push_back(*uv2);
	triangle3->gfx->material->uv->push_back(*uv3);

	triangle3->gfx->material->spec = specReflection;
	triangle3->gfx->material->shine = 0.3f;
	triangle3->gfx->material->texture = SINGLETONINSTANCE(MediaManager)->warrior;

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
	glDeleteBuffersARB(1, &(root->gfx->tboId));

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
*/