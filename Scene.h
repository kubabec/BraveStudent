#pragma once
#include "GL\freeglut.h"
#include <vector>
#include "SceneObject.h"
#include "Player.h"

class Scene
{
public:
	Scene(void);
	~Scene(void);

	void Render();
	void Update();

	void AddObject(SceneObject* object);
	void AddObject1(SceneObject* object);
	void AddObject2(SceneObject* object);
	void AddObject3(SceneObject* object);
	void AddObject4(SceneObject* object);
	void AddReward(SceneObject* object);
	void AddpreGameBox(SceneObject* object);


	void AddPlayerObject(Player* Player);


	void DisplayTextBackground();
	bool TextBackground; 
	SceneObject* preGameBox;

private:
	std::vector<SceneObject*> sceneObjects;
	std::vector<SceneObject*> sceneObjects1;
	std::vector<SceneObject*> sceneObjects2;
	std::vector<SceneObject*> sceneObjects3;
	std::vector<SceneObject*> sceneObjects4;
	std::vector<SceneObject*> Rewards;

	Player* PlayerObject;
};

