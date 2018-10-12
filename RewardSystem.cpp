#include "RewardSystem.h"
#include <cmath>
#include <ctime>


RewardSystem::RewardSystem(Scene* scene, Player* Player) {
	srand(time(NULL));
	SetOnCarSpots();
	vec3 RewardsColectionPos = vec3(-9.27, 1, -7);
	this->player = Player;
	placeIterator = 0;

	Model3D* ElvisReward = new Model3D("../Resources/Maps/elvis.bmp");
	ElvisReward->load("../Resources/Models/Rewards/elvisasreward.obj");
	Model3D* HTCViveReward = new Model3D("../Resources/Maps/htcvive.bmp");
	HTCViveReward->load("../Resources/Models/Rewards/htcvive.obj");
	Model3D* Projector = new Model3D("../Resources/Maps/projector.bmp");
	Projector->load("../Resources/Models/Rewards/projector.obj");
	Model3D* Microphone = new Model3D("../Resources/Maps/microphone.bmp");
	Microphone->load("../Resources/Models/Rewards/microphone.obj");


	RewardsHolder[0] = new Reward(Microphone, vec3(0.0, -7, 0.0), vec3(0.03, 0.03, 0.03), player, 4);
	scene->AddReward(RewardsHolder[0]); //Elvis 1 
	RewardsHolder[3] = new Reward(Microphone, vec3(0.0, -7, 0.0), vec3(0.03, 0.03, 0.03), player, 4);
	scene->AddReward(RewardsHolder[3]); //Elvis 4
	RewardsHolder[15] = new Reward(Microphone, vec3(0.0, -7, 0.0), vec3(0.03, 0.03, 0.03), player, 4);
	scene->AddReward(RewardsHolder[15]); //Elvis 1 
	RewardsHolder[16] = new Reward(Microphone, vec3(0.0, -7, 0.0), vec3(0.03, 0.03, 0.03), player, 4);
	scene->AddReward(RewardsHolder[16]); //Elvis 4
	RewardsHolder[21] = new Reward(Microphone, vec3(0.0, -7, 0.0), vec3(0.03, 0.03, 0.03), player, 4);
	scene->AddReward(RewardsHolder[21]); //Elvis 1 
	RewardsHolder[22] = new Reward(Microphone, vec3(0.0, -7, 0.0), vec3(0.03, 0.03, 0.03), player, 4);
	scene->AddReward(RewardsHolder[22]); //Elvis 4

	RewardsHolder[1] = new Reward(ElvisReward, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), player, 1);
	scene->AddReward(RewardsHolder[1]); //Elvis 2
	RewardsHolder[2] = new Reward(ElvisReward, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), player, 1);
	scene->AddReward(RewardsHolder[2]); //Elvis 3
	RewardsHolder[7] = new Reward(ElvisReward, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), player, 1);
	scene->AddReward(RewardsHolder[7]); //Elvis 2
	RewardsHolder[8] = new Reward(ElvisReward, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), player, 1);
	scene->AddReward(RewardsHolder[8]); //Elvis 3
	RewardsHolder[9] = new Reward(ElvisReward, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), player, 1);
	scene->AddReward(RewardsHolder[9]); //Elvis 2
	RewardsHolder[10] = new Reward(ElvisReward, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), player, 1);
	scene->AddReward(RewardsHolder[10]); //Elvis 3
	RewardsHolder[17] = new Reward(ElvisReward, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), player, 1);
	scene->AddReward(RewardsHolder[17]); //Elvis 2
	RewardsHolder[18] = new Reward(ElvisReward, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), player, 1);
	scene->AddReward(RewardsHolder[18]); //Elvis 3
	RewardsHolder[19] = new Reward(ElvisReward, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), player, 1);
	scene->AddReward(RewardsHolder[19]); //Elvis 2
	RewardsHolder[20] = new Reward(ElvisReward, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), player, 1);
	scene->AddReward(RewardsHolder[20]); //Elvis 3
	RewardsHolder[33] = new Reward(ElvisReward, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), player, 1);
	scene->AddReward(RewardsHolder[33]); //Elvis 3


	RewardsHolder[4] = new Reward(Projector, vec3(0.0, -7, 0.0), vec3(0.03, 0.03, 0.03), player, 3);
	scene->AddReward(RewardsHolder[4]); //Elvis 5 
	RewardsHolder[5] = new Reward(Projector, vec3(0.0, -7, 0.0), vec3(0.03, 0.03, 0.03), player, 3);
	scene->AddReward(RewardsHolder[5]); //Elvis 5 
	RewardsHolder[11] = new Reward(Projector, vec3(0.0, -7, 0.0), vec3(0.03, 0.03, 0.03), player, 3);
	scene->AddReward(RewardsHolder[11]); //Elvis 5 
	RewardsHolder[12] = new Reward(Projector, vec3(0.0, -7, 0.0), vec3(0.03, 0.03, 0.03), player, 3);
	scene->AddReward(RewardsHolder[12]); //Elvis 5 
	RewardsHolder[13] = new Reward(Projector, vec3(0.0, -7, 0.0), vec3(0.03, 0.03, 0.03), player, 3);
	scene->AddReward(RewardsHolder[13]); //Elvis 5 
	RewardsHolder[14] = new Reward(Projector, vec3(0.0, -7, 0.0), vec3(0.03, 0.03, 0.03), player, 3);
	scene->AddReward(RewardsHolder[14]); //Elvis 5 
	RewardsHolder[23] = new Reward(Projector, vec3(0.0, -7, 0.0), vec3(0.03, 0.03, 0.03), player, 3);
	scene->AddReward(RewardsHolder[23]); //Elvis 5 
	RewardsHolder[24] = new Reward(Projector, vec3(0.0, -7, 0.0), vec3(0.03, 0.03, 0.03), player, 3);
	scene->AddReward(RewardsHolder[24]); //Elvis 5 
	RewardsHolder[25] = new Reward(Projector, vec3(0.0, -7, 0.0), vec3(0.03, 0.03, 0.03), player, 3);
	scene->AddReward(RewardsHolder[25]); //Elvis 5 
	RewardsHolder[26] = new Reward(Projector, vec3(0.0, -7, 0.0), vec3(0.03, 0.03, 0.03), player, 3);
	scene->AddReward(RewardsHolder[26]); //Elvis 5 
	RewardsHolder[30] = new Reward(Projector, vec3(0.0, -7, 0.0), vec3(0.03, 0.03, 0.03), player, 3);
	scene->AddReward(RewardsHolder[30]); //Elvis 5 
	RewardsHolder[31] = new Reward(Projector, vec3(0.0, -7, 0.0), vec3(0.03, 0.03, 0.03), player, 3);
	scene->AddReward(RewardsHolder[31]); //Elvis 5 
	RewardsHolder[32] = new Reward(Projector, vec3(0.0, -7, 0.0), vec3(0.03, 0.03, 0.03), player, 3);
	scene->AddReward(RewardsHolder[32]); //Elvis 5 
	RewardsHolder[34] = new Reward(Projector, vec3(0.0, -7, 0.0), vec3(0.03, 0.03, 0.03), player, 3);
	scene->AddReward(RewardsHolder[34]); //Elvis 5 

	RewardsHolder[6] = new Reward(HTCViveReward, vec3(0.0, -7, 0.0), vec3(0.03, 0.03, 0.03), player, 2);
	scene->AddReward(RewardsHolder[6]); //Elvis 5 
	RewardsHolder[27] = new Reward(HTCViveReward, vec3(0.0, -7, 0.0), vec3(0.03, 0.03, 0.03), player, 2);
	scene->AddReward(RewardsHolder[27]); //Elvis 5 
	RewardsHolder[28] = new Reward(HTCViveReward, vec3(0.0, -7, 0.0), vec3(0.03, 0.03, 0.03), player, 2);
	scene->AddReward(RewardsHolder[28]); //Elvis 5 
	RewardsHolder[29] = new Reward(HTCViveReward, vec3(0.0, -7, 0.0), vec3(0.03, 0.03, 0.03), player, 2);
	scene->AddReward(RewardsHolder[29]); //Elvis 5 



	{

	RewardPositions[0].x = -2.13;
	RewardPositions[0].y = -6.6;
	RewardPositions[0].z = 10.19;

	RewardPositions[1].x = -5.08;
	RewardPositions[1].y = -6.6;
	RewardPositions[1].z = 9.28;

	RewardPositions[2].x = -7.67;
	RewardPositions[2].y = -6.6;
	RewardPositions[2].z = 5.49;

	RewardPositions[3].x = 7.97;
	RewardPositions[3].y = -6.6;
	RewardPositions[3].z = 5.34;

	RewardPositions[4].x = 0.09;
	RewardPositions[4].y = -6.6;
	RewardPositions[4].z = 2.2;

	RewardPositions[5].x = 3.09;
	RewardPositions[5].y = -6.6;
	RewardPositions[5].z = 8.87;

	RewardPositions[6].x = 4.07;
	RewardPositions[6].y = -6.6;
	RewardPositions[6].z = 11.57;

	RewardPositions[7].x = 0.13;
	RewardPositions[7].y = -15.82;
	RewardPositions[7].z = 30.22;

	RewardPositions[8].x = 1.69;
	RewardPositions[8].y = -15.87;
	RewardPositions[8].z = 30.14;

	RewardPositions[9].x = 8.00;
	RewardPositions[9].y = -15.87;
	RewardPositions[9].z = 26.04;

	RewardPositions[10].x = 0.04;
	RewardPositions[10].y = -15.87;
	RewardPositions[10].z = 26.64;

	RewardPositions[11].x = -8.57;
	RewardPositions[11].y = -15.87;
	RewardPositions[11].z = 21.88;

	RewardPositions[12].x = -15.27;
	RewardPositions[12].y = -15.87;
	RewardPositions[12].z = 21.12;

	RewardPositions[13].x = -15.42;
	RewardPositions[13].y = -15.87;
	RewardPositions[13].z = 24.37;


	RewardPositions[14].x = -13.56;
	RewardPositions[14].y = -15.87;
	RewardPositions[14].z = 25.92;

	RewardPositions[15].x = -11.22;
	RewardPositions[15].y = -15.87;
	RewardPositions[15].z = 29.77;

	RewardPositions[16].x = -8.51;
	RewardPositions[16].y = -15.87;
	RewardPositions[16].z = -14.11;

	RewardPositions[17].x = 0.24;
	RewardPositions[17].y = -15.87;
	RewardPositions[17].z = -6.87;

	RewardPositions[18].x = 0.68;
	RewardPositions[18].y = -15.87;
	RewardPositions[18].z = -5.40;

	RewardPositions[19].x = 4.00;
	RewardPositions[19].y = -15.87;
	RewardPositions[19].z = -3.56;

	RewardPositions[20].x = 4.41;
	RewardPositions[20].y = -15.87;
	RewardPositions[20].z = -9.52;

	RewardPositions[21].x = 1.05;
	RewardPositions[21].y = -15.87;
	RewardPositions[21].z = 0.20;

	RewardPositions[22].x = 7.73;
	RewardPositions[22].y = -15.87;
	RewardPositions[22].z = 2.78;

	RewardPositions[23].x = 4.68;
	RewardPositions[23].y = -15.87;
	RewardPositions[23].z = 1.12;

	RewardPositions[24].x = 4.35;
	RewardPositions[24].y = -15.87;
	RewardPositions[24].z = -4.57;

	RewardPositions[25].x = -1.76;
	RewardPositions[25].y = -15.87;
	RewardPositions[25].z = -8.73;

	RewardPositions[26].x = -3.33;
	RewardPositions[26].y = -15.87;
	RewardPositions[26].z = -7.12;

	RewardPositions[27].x = -11.62;
	RewardPositions[27].y = -15.87;
	RewardPositions[27].z = -8.66;

	RewardPositions[28].x = 8.32;
	RewardPositions[28].y = -15.87;
	RewardPositions[28].z = -5.87;

	RewardPositions[29].x = 4.19;
	RewardPositions[29].y = -15.87;
	RewardPositions[29].z = -1.76;

	RewardPositions[30].x = -1.29;
	RewardPositions[30].y = -6.6;
	RewardPositions[30].z = 11.0;

	RewardPositions[31].x = -2.35;
	RewardPositions[31].y = -6.6;
	RewardPositions[31].z = 7.68;

	RewardPositions[32].x = 1.45;
	RewardPositions[32].y = -6.6;
	RewardPositions[32].z = 0.93;

	RewardPositions[33].x = 0.44;
	RewardPositions[33].y = -6.6;
	RewardPositions[33].z = 3.3;

	RewardPositions[34].x = 2.92;
	RewardPositions[34].y = -6.6;
	RewardPositions[34].z = 1.28;

	RewardPositions[35].x = 1.82;
	RewardPositions[35].y = -6.6;
	RewardPositions[35].z = 9.77;

	RewardPositions[36].x = 4.16;
	RewardPositions[36].y = -6.6;
	RewardPositions[36].z = 8.10;

	RewardPositions[37].x = 5.59;
	RewardPositions[37].y = -6.6;
	RewardPositions[37].z = 6.29;

	RewardPositions[38].x = 2.10;
	RewardPositions[38].y = -15.87;
	RewardPositions[38].z = 28.04;

	RewardPositions[39].x = 0.14;
	RewardPositions[39].y = -15.87;
	RewardPositions[39].z = 27.9;

	RewardPositions[40].x = 4.20;
	RewardPositions[40].y = -15.87;
	RewardPositions[40].z = 26.0;

	RewardPositions[41].x = -6.26;
	RewardPositions[41].y = -15.87;
	RewardPositions[41].z = 25.87;

	RewardPositions[42].x = -13.83;
	RewardPositions[42].y = -15.87;
	RewardPositions[42].z = 21.51;

	RewardPositions[43].x = -13.45;
	RewardPositions[43].y = -15.87;
	RewardPositions[43].z = 23.20;

	RewardPositions[44].x = -13.3;
	RewardPositions[44].y = -15.87;
	RewardPositions[44].z = 24.1;

	RewardPositions[45].x = -13.11;
	RewardPositions[45].y = -15.87;
	RewardPositions[45].z = 24.87;

	RewardPositions[46].x = -13.59;
	RewardPositions[46].y = -15.87;
	RewardPositions[46].z = 26.83;

	RewardPositions[47].x = -13.31;
	RewardPositions[47].y = -15.87;
	RewardPositions[47].z = 27.7;

	RewardPositions[48].x = -13.07;
	RewardPositions[48].y = -15.87;
	RewardPositions[48].z = 28.63;

	RewardPositions[49].x = -10.93;
	RewardPositions[49].y = -15.87;
	RewardPositions[49].z = 27.34;

	RewardPositions[50].x = -9.63;
	RewardPositions[50].y = -15.87;
	RewardPositions[50].z = 23.83;

	RewardPositions[51].x = -10.1;
	RewardPositions[51].y = -15.87;
	RewardPositions[51].z = 26.79;

	RewardPositions[52].x = -7.06;
	RewardPositions[52].y = -15.87;
	RewardPositions[52].z = -9.79;

	RewardPositions[53].x = -9.83;
	RewardPositions[53].y = -15.87;
	RewardPositions[53].z = -10.96;

	RewardPositions[54].x = 7.74;
	RewardPositions[54].y = -15.87;
	RewardPositions[54].z = -9.73;

	RewardPositions[55].x = 4.72;
	RewardPositions[55].y = -15.87;
	RewardPositions[55].z = -5.87;

	RewardPositions[56].x = 2.12;
	RewardPositions[56].y = -15.87;
	RewardPositions[56].z = -5.83;

	RewardPositions[57].x = 8.30;
	RewardPositions[57].y = -15.87;
	RewardPositions[57].z = -7.64;

	RewardPositions[58].x = 6.17;
	RewardPositions[58].y = -15.87;
	RewardPositions[58].z = -5.96;

	RewardPositions[59].x = 3.49;
	RewardPositions[59].y = -15.87;
	RewardPositions[59].z = 1.97;

	RewardPositions[60].x = 0.45;
	RewardPositions[60].y = -15.87;
	RewardPositions[60].z = -7.99;

	RewardPositions[61].x = 3.26;
	RewardPositions[61].y = -15.87;
	RewardPositions[61].z = -7.49;

	RewardPositions[62].x = 8.55;
	RewardPositions[62].y = -15.87;
	RewardPositions[62].z = -3.51;

	RewardPositions[63].x = 6.40;
	RewardPositions[63].y = -15.87;
	RewardPositions[63].z = 0.55;

	RewardPositions[64].x = 3.65;
	RewardPositions[64].y = -15.87;
	RewardPositions[64].z = 1.22;

	RewardPositions[65].x = -11.76;
	RewardPositions[65].y = -15.87;
	RewardPositions[65].z = -13.92;

	RewardPositions[66].x = -10.39;
	RewardPositions[66].y = -15.87;
	RewardPositions[66].z = -12.34;

	RewardPositions[67].x = -9.67;
	RewardPositions[67].y = -15.87;
	RewardPositions[67].z = -8.44;

	RewardPositions[68].x = 6.73;
	RewardPositions[68].y = -15.87;
	RewardPositions[68].z = -9.23;

	RewardPositions[69].x = 1.37;
	RewardPositions[69].y = -15.87;
	RewardPositions[69].z = -8.99;

	RewardPositions[70].x = 7.03;
	RewardPositions[70].y = -15.87;
	RewardPositions[70].z = -5.71;

	RewardPositions[71].x = -0.08;
	RewardPositions[71].y = -15.87;
	RewardPositions[71].z = -3.45;

	RewardPositions[72].x = 3.56;
	RewardPositions[72].y = -15.87;
	RewardPositions[72].z = -5.21;


}

	for (int i = 0; i < 73; i++)
		lookupTable[i] = 0;


	for (int i = 0; i < 35; i++) {
		int a = rand() % 73;
		while(lookupTable[a] != 0 )
			a = rand() % 73;

		RewardsHolder[i]->pos.x = RewardPositions[a].x;
		RewardsHolder[i]->pos.y = RewardPositions[a].y;
		RewardsHolder[i]->pos.z = RewardPositions[a].z;
		lookupTable[a] = 1;
		


	}
	


	//CheckPlayerRewardColision();
}



bool RewardSystem::canPlayerGetReward(int a) {
	float x = player->pos.x - RewardsHolder[a]->pos.x;
	float y = player->pos.y - RewardsHolder[a]->pos.y;
	float z = player->pos.z - RewardsHolder[a]->pos.z; 

	float distance = sqrt(pow(x,2) + pow(y,2) + pow(z,2));

	if (distance < 0.3 && RewardsHolder[a]->isCompleted == false) return 1;
	else return 0;
}

bool RewardSystem::CheckPlayerRewardColision() {
	if (!player->isAlreadyCarryingReward) {
		for (int i = 0; i < 35; i++) {
			if (canPlayerGetReward(i)) {
				player->isAlreadyCarryingReward = true;
				RewardsHolder[i]->isHeldByPlayer = true;
				player->HeldRewardID = i;
				RewardsHolder[i]->pos = player->pos;
				return true;
			}
		}
	}
	return false;
}

void RewardSystem::CheckIfRewardDelivered() {
	float x = player->pos.x - (-9.64);
	float z = player->pos.z - (-8);
	float distance = sqrt(pow(x, 2) + pow(z, 2));

	if (player->isAlreadyCarryingReward && distance < 0.5 && player->isOnLevel0) {
		placeIterator += 1; //// TUTAJ ZWIEKSZAM TEN ITERATOR 
		int collctedRewardType = RewardsHolder[player->HeldRewardID]->RewardType;
		player->CollectedRewards[collctedRewardType] += 1;

		player->score += RewardsHolder[player->HeldRewardID]->value;

		player->isAlreadyCarryingReward = false;
	
		RewardsHolder[player->HeldRewardID]->isCompleted = true;
		RewardsHolder[player->HeldRewardID]->OnCarPlace=  OnCarSpots[placeIterator];
		//RewardsHolder[player->HeldRewardID]->OnCarPlace = OnCarSpots[1];
		//printf("%d \n", OnCarSpots[player->RewardsCollectionCounter - 1].x);
	//	printf("%d", RewardsHolder[player->HeldRewardID]->OnCarPlace);
		RewardsHolder[player->HeldRewardID]->isHeldByPlayer = false;

	}
}


void RewardSystem::SetOnCarSpots() {
	float x = -9.95;
	float y = 0.42;
	float z = -9.2;
//	(-9.97, 0.54, -9.2);
	for (int i = 1; i < 30; i++) {
		OnCarSpots[i] = vec3(x, y, z);
		x += 0.25;

		if (i % 3 == 0 && i != 0) {
			z += 0.15;
			x = -9.95;
		}
		if (i % 12 == 0 && i != 0) {
			y += 0.09;
			x = -9.95;
			z = -9.2;
		}
	}

}