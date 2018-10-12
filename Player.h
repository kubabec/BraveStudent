#pragma once
#include "SceneObject.h"
#include "GL\freeglut.h"
#include <vector>

class Player :
	public SceneObject
{
public:
	Player();
	~Player();

	void Render();
	void Update();
	void LevelSwitch(int);
	void DefineColisions();
	void DetectColision();

	void DirectionCorrection();


	vec3 dir;
	float speed;
	vec3 oldPos;
	float level_0[24][4];
	float level_1[43][4];
	float level_2[4][4];
	float level_3[42][4];
	float level_4[56][4];
	int score;
	int HeldRewardID;
	float velocity_vertical;
	float velocity_horizontal;
	int CollectedRewards[5];

	bool flyingMode;
	bool isOnLevel0;
	bool isOnLevel1;
	bool isOnLevel2;
	bool isOnLevel3;
	bool isOnLevel4;
	int CurrentLevel;
	bool ReactOnColisions; 
	bool isAlreadyCarryingReward; 
};

