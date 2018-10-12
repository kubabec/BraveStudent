#include "vec3.h"
#include "Scene.h"
#include "Sphere.h"

Scene::Scene(void)
{
	TextBackground = false;

}


Scene::~Scene(void)
{
	for(unsigned int i = 0 ; i < sceneObjects.size() ; i++)
		delete sceneObjects[i];
	for (unsigned int i = 0; i < sceneObjects1.size(); i++)
		delete sceneObjects1[i];
	for (unsigned int i = 0; i < sceneObjects3.size(); i++)
		delete sceneObjects3[i];
	for (unsigned int i = 0; i < sceneObjects4.size(); i++)
		delete sceneObjects4[i];


	sceneObjects.clear();
	sceneObjects1.clear();
	sceneObjects3.clear();
	sceneObjects4.clear();
}

void Scene::AddReward(SceneObject* object)
{
	Rewards.push_back(object);
}

void Scene::AddObject(SceneObject* object)
{
	sceneObjects.push_back(object);
}

void Scene::AddObject1(SceneObject* object)
{
	sceneObjects1.push_back(object);
}
void Scene::AddObject2(SceneObject* object)
{
	sceneObjects2.push_back(object);
}
void Scene::AddObject3(SceneObject* object)
{
	sceneObjects3.push_back(object);
}

void Scene::AddObject4(SceneObject* object)
{
	sceneObjects4.push_back(object);
}


void Scene::AddPlayerObject(Player* Player) {
	PlayerObject = Player;
}





void Scene::AddpreGameBox(SceneObject* object) {
	this->preGameBox = object;
}
void Scene::DisplayTextBackground() {
	preGameBox->Render();
}

void Scene::Render()
{
	Sleep(15);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//glLoadIdentity();
	float l0_amb[] = { 1.f, 1.f, 1.f, 1.0f };
	float l0_dif[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	float l0_spe[] = { 0.0f, 0.0f, 0.0f, 1.f };
	float l0_pos[] = { 0.0f, 15.f, -7.0f, 0.0f };
	float l0_pos1[] = { -3.82f, -2.9, 1.27,  0.0f };
	float l0_pos2[] = { -4.08, -10.86, 53.68,  0.0f };
	float l0_pos3[] = { -4.15f, -12.44f, 21.f, 0.0f };
	float l0_pos4[] = { -1.24, -11.75, -13.82, 0.0f };


	glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
	glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, l0_amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, l0_dif);
	glLightfv(GL_LIGHT1, GL_SPECULAR, l0_spe);
	glLightfv(GL_LIGHT1, GL_POSITION, l0_pos1);
	glLightfv(GL_LIGHT2, GL_AMBIENT, l0_amb);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, l0_dif);
	glLightfv(GL_LIGHT2, GL_SPECULAR, l0_spe);
	glLightfv(GL_LIGHT2, GL_POSITION, l0_pos2);

	glLightfv(GL_LIGHT3, GL_AMBIENT, l0_amb);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, l0_dif);
	glLightfv(GL_LIGHT3, GL_SPECULAR, l0_spe);
	glLightfv(GL_LIGHT3, GL_POSITION, l0_pos3);

	glLightfv(GL_LIGHT4, GL_AMBIENT, l0_amb);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, l0_dif);
	glLightfv(GL_LIGHT4, GL_SPECULAR, l0_spe);
	glLightfv(GL_LIGHT4, GL_POSITION, l0_pos4);

	if (TextBackground) {
		DisplayTextBackground();
		TextBackground = false;
	}


	
	PlayerObject->Render();
	for (unsigned int i = 0; i < Rewards.size(); i++)
		Rewards[i]->Render();

	if (PlayerObject->isOnLevel0) {
		for (unsigned int i = 0; i < sceneObjects.size(); i++)
			sceneObjects[i]->Render();
	}
	else if (PlayerObject->isOnLevel1) {
		for (unsigned int i = 0; i < sceneObjects1.size(); i++)
			sceneObjects1[i]->Render();
	}
	else if (PlayerObject->isOnLevel2) {
		for (unsigned int i = 0; i < sceneObjects2.size(); i++)
			sceneObjects2[i]->Render();
	}
	else if (PlayerObject->isOnLevel3) {
		for (unsigned int i = 0; i < sceneObjects3.size(); i++)
			sceneObjects3[i]->Render();
	}
	else if (PlayerObject->isOnLevel4)
	{
		for (unsigned int i = 0; i < sceneObjects4.size(); i++)
			sceneObjects4[i]->Render();
	}
}

void Scene::Update()
{
	PlayerObject->Update();
	for(unsigned int i = 0 ; i < sceneObjects.size() ; i++)
		sceneObjects[i]->Update();
	for (unsigned int i = 0; i < sceneObjects1.size(); i++)
		sceneObjects1[i]->Update();
	for (unsigned int i = 0; i < sceneObjects2.size(); i++)
		sceneObjects2[i]->Update();
	for (unsigned int i = 0; i < sceneObjects3.size(); i++)
		sceneObjects3[i]->Update();
	for (unsigned int i = 0; i < sceneObjects4.size(); i++)
		sceneObjects4[i]->Update();
}