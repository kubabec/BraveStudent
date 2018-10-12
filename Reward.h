#pragma once
#include "GL\freeglut.h"
#include "SceneObject.h"
#include "Model3D.h"
#include "Player.h"
#include <vector>

class Reward : public SceneObject {
public:
	Reward(Model3D* model, vec3 pos, vec3 scale, Player* player, int type);
	~Reward();
	void Render();
	void Update();
	Model3D* model;
	vec3 pos;
	vec3 scale;
	float rotation;
	float resize;
	bool resizeFlag;
	bool isHeldByPlayer;
	Player* player;
	vec3 PrevMousePosition;
	float rotationZ;
	int RewardType;
	int value;
	bool isCompleted;
	vec3 OnCarPlace;

};
