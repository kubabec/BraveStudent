#pragma once
#include <vector>
#include "vec3.h"
#include "Reward.h"
#include "Model3D.h"
#include "Scene.h"
#include "Player.h"

class RewardSystem 
{ 
public:
	RewardSystem(Scene* scene, Player* player);
	~RewardSystem();

	Reward* RewardsHolder[35];
	Player* player; 
	vec3 RewardPositions[73];
	int lookupTable[73];
	Scene* scene;

	bool canPlayerGetReward(int);
	bool CheckPlayerRewardColision();
	void CheckIfRewardDelivered();

	vec3 RewardsColectionPos ;
	int placeIterator;
	vec3 OnCarSpots[30];
	void SetOnCarSpots();
	};
