#include <Game/SceneData.hpp>
#include <Game/Camera.hpp>
#include <Managers/SceneGraphManager.hpp>
#include <Managers/MediaManager.hpp>
#include <Managers/LightingManager.hpp>
#include <Game/PathPlanner.hpp>

SceneGraphManager *createGraph()
{
	int lightIndex = SINGLETONINSTANCE(LightingManager)->getAvailableLightIndex();
	SINGLETONINSTANCE(LightingManager)->lights[lightIndex].enable(true);
	SINGLETONINSTANCE(LightingManager)->lights[lightIndex].setDiffuse(0.5f,0.5f,0.5f, 1.0f);
	SINGLETONINSTANCE(LightingManager)->lights[lightIndex].setSpecular(0.7f,0.2f,0.1f, 1.0f);
	SINGLETONINSTANCE(LightingManager)->lights[lightIndex].setAmbient(0.2f,0.2f,0.2f, 1.0f);
	SINGLETONINSTANCE(LightingManager)->lights[lightIndex].setPos(10.0f,10.0f,10.0f);

	auto root = new Object();
	root->Name = "Root";
	root->transformation->Reset();

	auto ground = new Object();
	ground->Name = "Ground";
	//player->gfx = SINGLETONINSTANCE( MediaManager )->playerModel;
	ground->model =  SINGLETONINSTANCE( MediaManager )->ground;
	ground->transformation->Reset();
	ground->transformation->Scale(2,2,1);
	ground->transformation->Translate(9, 9, 0);

	auto player = new Object();
	player->Name = "Player";
	//player->gfx = SINGLETONINSTANCE( MediaManager )->playerModel;
	player->model =  SINGLETONINSTANCE( MediaManager )->crazyModel;
	player->transformation->Reset();
	player->transformation->Rotate(90,1.0f,0.0f,0.0f);
	player->transformation->Translate(18, 0, -20);
	//player->transformation->Translate(18, 20, 0);
	//player->transformation->Translate(0, 1, 0);
	//player->transformation->Rotate(90,0.0f,0.0f,1.0f);

	auto box = new Object();
	box->Name = "Box";
	box->model =  SINGLETONINSTANCE( MediaManager )->boxModel;
	box->transformation->Reset();
	box->transformation->Scale(20,20,20);
	box->transformation->Translate(1.0f,1.0f,0);

	auto box1 = new Object();
	box1->Name = "Box";
	box1->model =  SINGLETONINSTANCE( MediaManager )->boxModel;
	box1->transformation->Reset();
	box1->transformation->Scale(20,20,20);
	box1->transformation->Translate(1.1f,1.1f,0);

	auto box2 = new Object();
	box2->Name = "Box";
	box2->model =  SINGLETONINSTANCE( MediaManager )->boxModel;
	box2->transformation->Reset();
	box2->transformation->Scale(22,22,22);
	box2->transformation->Translate(0.8f,1.15f,0);

	auto box3 = new Object();
	box3->Name = "Box";
	box3->model =  SINGLETONINSTANCE( MediaManager )->boxModel;
	box3->transformation->Reset();
	box3->transformation->Scale(17,17,17);
	box3->transformation->Translate(0.7f,1.3f,0);

	auto box4 = new Object();
	box4->Name = "Box";
	//player->gfx = SINGLETONINSTANCE( MediaManager )->playerModel;
	box4->model =  SINGLETONINSTANCE( MediaManager )->boxModel;
	box4->transformation->Reset();
	box4->transformation->Scale(30,30,30);
	box4->transformation->Translate(0.9f,0.75f,0);
	
	//box->transformation->Translate(1.0f,0.0f,0.0f);

	/*
	Matrix4x4f *temp = new Matrix4x4f();
	temp = temp->createRotate(90, 0.0f,0.0f,1.0f);
	temp->MultiplyWith(*temp->createTranslate(0,1,0));
	temp->MultiplyWith(*temp->createTranslate(1,0,0));
	
	player->transformation->MultiplyWith(*temp);
	*/
	
	//player->transformation->Rotate(90,0.0f,0.0f,1.0f);
	
	//player->transformation->Translate(0,1,0);
	//player->transformation->Translate(1,0,0);
	
	/*auto car = new Object();
	car->Name = "Car";
	car->model =  SINGLETONINSTANCE( MediaManager )->carModel;
	car->transformation->Reset();
	
	car->transformation->Rotate(90,1.0f,0.0f,0.0f);
	//car->transformation->Translate(-3,0,0);
	*/
	//std::cout << "num of vertices: " << player->gfx->numVertices << std::endl;
	/*for(int i = 0; i < player->gfx->numMaterials; i++)
	{
		player->gfx->SetTexture(SINGLETONINSTANCE( MediaManager )->playerTex, &player->gfx->mMaterials[i]);
	}*/
	
	auto m = new Matrix4x4f();
	m->Translate(0.0f, 0.0f, -4.0f);
	
	root->children->push_back(*ground);
	root->children->push_back(*box);
	root->children->push_back(*box1);
	root->children->push_back(*box2);
	root->children->push_back(*box3);
	root->children->push_back(*box4);
	root->children->push_back(*player);
	
	//root->children->push_back(*car);


	auto camera = new Camera();
	camera->Position.SetX(18);
	camera->Position.SetY(18);
	camera->Position.SetZ(30);
	//camera->MoveCamera3D(new Vector3f(0, 0, 100));
	camera->LookAt.SetX(18);
	camera->LookAt.SetY(18);
	camera->LookAt.SetZ(-1);
	camera->Up.SetX(0);
	camera->Up.SetY(1);
	camera->Up.SetZ(0);
	//camera->Up = *(new Vector3f(1, 1, 0));

	SceneGraphManager *sceneGraph = new SceneGraphManager(camera, root);
	SINGLETONINSTANCE(PathPlanner)->StartUp();//sceneGraph);
	return sceneGraph;
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