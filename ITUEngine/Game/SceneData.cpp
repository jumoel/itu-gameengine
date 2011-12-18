#include <Game/SceneData.hpp>
#include <Game/Camera.hpp>
#include <Managers/SceneGraphManager.hpp>
#include <Managers/MediaManager.hpp>
#include <Managers/LightingManager.hpp>
#include <Subsystems/Physics/PhysicsModels/PhysicsModel.hpp>
#include <Subsystems/Physics/PhysicsSystem.hpp>
#include <PlayerInteraction.hpp>

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

	float mapWidth = 40.0f;
	auto ground = new Object();
	ground->Name = "Ground";
	ground->model =  SINGLETONINSTANCE( MediaManager )->ground;
	ground->transformation->Reset();
	ground->SetPos2D(20.0f,20.0f);
	ground->SetScale(mapWidth,mapWidth,1.0f);
	SINGLETONINSTANCE(PathPlanner)->StartUp(mapWidth);

	auto underground = new Object();
	underground->Name = "Underground";
	underground->model =  SINGLETONINSTANCE( MediaManager )->ground;
	underground->transformation->Reset();
	underground->SetPos2D(20.0f,20.0f);
	underground->SetScale(mapWidth*10,mapWidth*10,1.0f);

	Point point;
	point.X = 0.0f;
	point.Y = 0.0f;

	Point forward;
	forward.X = 0;
	forward.Y = -1;
	forward = forward.GetNormalizedPoint();

	auto player = new Object();
	SINGLETONINSTANCE(PlayerInteraction)->StartUp(player);

	player->Name = "Player";
	player->model =  SINGLETONINSTANCE( MediaManager )->crazyModel;
	MovingObjectModel* tempMovingObject = new MovingObjectModel(CIRCULARSHAPE, PLAYERTYPE, forward, player);
	player->physicsModel = tempMovingObject;
	//player->physicsModel = new MovingObjectModel(CIRCULARSHAPE, PLAYERTYPE, forward, player);
	Circle circle(Point(0.0f,0.0f),0.5f);
	player->physicsModel->InitializeAsCircle(circle);
	SINGLETONINSTANCE(PhysicsSystem)->AddMovingObject(tempMovingObject);
	player->SetPos2D(5,35);
	player->Rotate(90.0f, 1.0f, 0.0f, 0.0f);
	player->SetForward(0.0f, 1.0f);
	player->setLookAt2D(forward.X,forward.Y);
	
	//player->
	//player->physicsModel->debug();

	Rectangle physicsBox(Point(-0.5f, -0.5f), 1.0f, 1.0f);

	auto box = new Object();
	box->Name = "Box";
	box->model =  SINGLETONINSTANCE( MediaManager )->boxModel;
	StaticObjectModel* tempStaticObject = new StaticObjectModel(RECTANGULARSHAPE);
	box->physicsModel = tempStaticObject;
	box->physicsModel->InitializeAsRectangle(physicsBox);
	SINGLETONINSTANCE(PhysicsSystem)->AddStaticObject(tempStaticObject);
	box->SetPos2D(20.0f, 0.0f);
	box->SetScale(40.0f, 1.0f, 3.0f);
	//box->physicsModel->debug();
	
	auto box1 = new Object();
	box1->Name = "Box1";
	tempStaticObject = new StaticObjectModel(RECTANGULARSHAPE);
	box1->model =  SINGLETONINSTANCE( MediaManager )->boxModel;
	box1->physicsModel = tempStaticObject;
	box1->physicsModel->InitializeAsRectangle(physicsBox);
	SINGLETONINSTANCE(PhysicsSystem)->AddStaticObject(tempStaticObject);
	box1->SetPos2D(20.0f, 40.0f);
	box1->SetScale(40.0f, 1.0f, 3.0f);

	auto box2 = new Object();
	box2->Name = "Box2";
	box2->model =  SINGLETONINSTANCE( MediaManager )->boxModel;
	tempStaticObject = new StaticObjectModel(RECTANGULARSHAPE);
	box2->physicsModel = tempStaticObject;
	box2->physicsModel->InitializeAsRectangle(physicsBox);
	SINGLETONINSTANCE(PhysicsSystem)->AddStaticObject(tempStaticObject);
	box2->SetPos2D(0.0f, 20.0f);
	box2->SetScale(1.0f, 40.0f, 3.0f);

	auto box3 = new Object();
	box3->Name = "Box3";
	box3->model =  SINGLETONINSTANCE( MediaManager )->boxModel;
	tempStaticObject = new StaticObjectModel(RECTANGULARSHAPE);
	box3->physicsModel = tempStaticObject;
	box3->physicsModel->InitializeAsRectangle(physicsBox);
	SINGLETONINSTANCE(PhysicsSystem)->AddStaticObject(tempStaticObject);
	box3->SetPos2D(40.0f, 20.0f);
	box3->SetScale(1.0f, 40.0f, 3.0f);

	auto box4 = new Object();
	box4->Name = "Box4";
	box4->model =  SINGLETONINSTANCE( MediaManager )->boxModel;
	tempStaticObject = new StaticObjectModel(RECTANGULARSHAPE);
	box4->physicsModel = tempStaticObject;
	box4->physicsModel->InitializeAsRectangle(physicsBox);
	SINGLETONINSTANCE(PhysicsSystem)->AddStaticObject(tempStaticObject);
	box4->SetPos2D(27.0f, 15.0f);
	box4->SetScale(1.0f, 30.0f, 3.0f);

	auto box5 = new Object();
	box5->Name = "Box5";
	box5->model =  SINGLETONINSTANCE( MediaManager )->boxModel;
	tempStaticObject = new StaticObjectModel(RECTANGULARSHAPE);
	box5->physicsModel = tempStaticObject;
	box5->physicsModel->InitializeAsRectangle(physicsBox);
	SINGLETONINSTANCE(PhysicsSystem)->AddStaticObject(tempStaticObject);
	box5->SetPos2D(13.0f, 25.0f);
	box5->SetScale(1.0f, 30.0f, 3.0f);
	

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
	
	
	root->children->push_back(*underground);
	root->children->push_back(*ground);
	
	root->children->push_back(*box);
	root->children->push_back(*box1);
	root->children->push_back(*box2);
	root->children->push_back(*box3);
	root->children->push_back(*box4);
	root->children->push_back(*box5);
	
	root->children->push_back(*player);
	
	//root->children->push_back(*car);

	//std::cout << "Cosine of 90 = " << cosf(90.0f) << endl;
	SINGLETONINSTANCE(PhysicsSystem)->SetStaticPathMap();
	player->physicsModel->SetTargetPosition(new Point(50,5));

	auto camera = new Camera();
	camera->Position.SetX(20);
	camera->Position.SetY(5);
	camera->Position.SetZ(50);
	camera->LookAt.SetX(20);
	camera->LookAt.SetY(20);
	camera->LookAt.SetZ(-1);
	camera->Up.SetX(0);
	camera->Up.SetY(1);
	camera->Up.SetZ(0);

	SceneGraphManager *sceneGraph = new SceneGraphManager(camera, root);

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