#include "vec3.h"
#include "Player.h"



Player::Player()
{

	pos.x = -11.31f;
	pos.y = 1.0f;
	pos.z = -16.67f;

	dir.x = -1;
	dir.y = 0;
	dir.z = -2;

	speed = .03f;
	score = 0;

	velocity_horizontal = 0;
	velocity_vertical = 0;

	flyingMode = false;
	isOnLevel0 = true;
	CurrentLevel = 0;
	isOnLevel1 = false;
	isOnLevel2 = false;
	isOnLevel3 = false;
	isOnLevel4 = false;
	isAlreadyCarryingReward = false; 

	ReactOnColisions = true;
	DefineColisions();

	for (int i = 1; i < 5; i++) {
		CollectedRewards[i] = 0;
	}

}


Player::~Player()
{
}

void Player::Render()
{

}

void Player::Update()
{
	oldPos.x = pos.x;
	oldPos.z = pos.z;

	pos.x += dir.x * speed * velocity_vertical;
	pos.z += dir.z * speed * velocity_vertical;

	pos.x += dir.z * speed * velocity_horizontal;
	pos.z -= dir.x * speed * velocity_horizontal;

	if (flyingMode)
		pos.y += dir.y * speed * velocity_vertical;
	else {
		if (isOnLevel1) {
			pos.y = -6.45;
		}
		else if (isOnLevel4 || isOnLevel3 || isOnLevel2) {
			pos.y = -15.67;
		}
		else
			pos.y = 0.5;
	}

	velocity_vertical = 0;
	velocity_horizontal =0;

	DetectColision();

}


void Player::LevelSwitch(int Direction) {
	if (Direction == 1) {
		switch (CurrentLevel) {
		case 0:
				isOnLevel1 = true;
				isOnLevel0 = false;
				pos.x = -4.14;
				pos.z = 3.3;
				DirectionCorrection();
				break;
		case 1:
				isOnLevel2 = true;
				isOnLevel1 = false;
				pos.x = -4.13;
				pos.z = 48.9;
				DirectionCorrection();

				break;
		case 2:
				isOnLevel3 = true;
				isOnLevel2= false;
				pos.x = -3.91;
				pos.z = 23.85;
				DirectionCorrection();

				break;
		case 3:
				isOnLevel4 = true;
				isOnLevel3 = false;
				pos.x = -3.91;
				pos.z = -11.95;
				DirectionCorrection();

			break;
		}
		CurrentLevel = CurrentLevel + 1;
		if (CurrentLevel > 4) CurrentLevel = 4;
	}


	if (Direction == 0) {
		switch (CurrentLevel) {
		case 1:
				isOnLevel0 = true;
				isOnLevel1 = false;
				pos.x = -4.24;
				pos.z = -0.53;
				DirectionCorrection();
			break;

		case 2:
			isOnLevel1 = true;
			isOnLevel2 = false;
			pos.x = -4.14;
			pos.z = 3.3;
			DirectionCorrection();

			break;

		case 3:
				isOnLevel2 = true;
				isOnLevel3 = false;
				pos.x = -4.13;
				pos.z = 48.9;
				DirectionCorrection();

			break;
		case 4:
				isOnLevel3 = true;
				isOnLevel4 = false;
				pos.x = -3.91;
				pos.z = 23.85;
				DirectionCorrection();

			break;
		}
		CurrentLevel = CurrentLevel - 1;
		if (CurrentLevel < 0) CurrentLevel = 0;

	}

}


void Player::DirectionCorrection() {
	if (isOnLevel0) {
		dir.x = 0;
		dir.y = 0;
		dir.z = -1;
	}
	else {
		dir.x = 0;
		dir.y = 0;
		dir.z = 1;
	}
}

void Player::DetectColision() {
	if (ReactOnColisions) {
		if (isOnLevel0) {
			for (int i = 0; i < 24; i++) {
				if (pos.x >= level_0[i][0] && pos.x <= level_0[i][1] && pos.z >= level_0[i][2] && pos.z <= level_0[i][3])
				{
					pos.x = oldPos.x;
					pos.z = oldPos.z;
				}
			}
		}
		else
			if (isOnLevel1) {
				for (int i = 0; i < 43; i++) {
					if (pos.x >= level_1[i][0] && pos.x <= level_1[i][1] && pos.z >= level_1[i][2] && pos.z <= level_1[i][3])
					{
						pos.x = oldPos.x;
						pos.z = oldPos.z;
					}
				}
			}
			else
				if (isOnLevel2) {
					for (int i = 0; i < 4; i++) {
						if (pos.x >= level_2[i][0] && pos.x <= level_2[i][1] && pos.z >= level_2[i][2] && pos.z <= level_2[i][3])
						{
							pos.x = oldPos.x;
							pos.z = oldPos.z;
						}
					}
				}
			else
				if (isOnLevel3) {
					for (int i = 0; i < 42; i++) {
						if (pos.x >= level_3[i][0] && pos.x <= level_3[i][1] && pos.z >= level_3[i][2] && pos.z <= level_3[i][3])
						{
							pos.x = oldPos.x;
							pos.z = oldPos.z;
						}
					}
				}
				else
					if (isOnLevel4) {
						for (int i = 0; i < 56; i++) {
							if (pos.x >= level_4[i][0] && pos.x <= level_4[i][1] && pos.z >= level_4[i][2] && pos.z <= level_4[i][3])
							{
								pos.x = oldPos.x;
								pos.z = oldPos.z;
							}
						}
					}
	}
}

void Player::DefineColisions() {

	// Kolizje z pietrem 0
	{
		{	//1  2
			level_0[0][0] = -15.4;
			level_0[0][1] = -14.55;
			level_0[0][2] = -17.2;
			level_0[0][3] = 6.59;
		}
		{	//3
			level_0[1][0] = -14.99;
			level_0[1][1] = -8.03;
			level_0[1][2] = 6.29;
			level_0[1][3] = 7.12;
		}
		{	//4
			level_0[2][0] = -3.30;
			level_0[2][1] = 6.10;
			level_0[2][2] = -0.2;
			level_0[2][3] = 7.49;
		}
		{	//5
			level_0[3][0] = 1.99;
			level_0[3][1] = 3.84;
			level_0[3][2] = -7.72;
			level_0[3][3] = 0.13;
		}
		{	//6
			level_0[4][0] = -8.18;
			level_0[4][1] = 3.37;
			level_0[4][2] = -13.1;
			level_0[4][3] = -6.47;
		}
		{	//7
			level_0[5][0] = -6.48;
			level_0[5][1] = -5.67;
			level_0[5][2] = -18.08;
			level_0[5][3] = -12.46;
		}
		{	//8
			level_0[6][0] = -15.30;
			level_0[6][1] = -6.21;
			level_0[6][2] = -17.89;
			level_0[6][3] = -16.99;
		}
		{	//9
			level_0[7][0] = -13.05;
			level_0[7][1] = -12.95;
			level_0[7][2] = -15.05;
			level_0[7][3] = -14.96;
		}
		{	//10
			level_0[8][0] = -13.25;
			level_0[8][1] = -13.15;
			level_0[8][2] = -13.06;
			level_0[8][3] = -12.95;
		}
		{	//11
			level_0[9][0] = -12.88;
			level_0[9][1] = -12.72;
			level_0[9][2] = -10.08;
			level_0[9][3] = -9.91;
		}
		{	//12
			level_0[10][0] = -13.28;
			level_0[10][1] = -13.08;
			level_0[10][2] = -7.09;
			level_0[10][3] = -6.88;
		}
		{	//13
			level_0[11][0] = -13.08;
			level_0[11][1] = -12.91;
			level_0[11][2] = -5.09;
			level_0[11][3] = -4.92;
		}
		{	//14
			level_0[12][0] = -15.12;
			level_0[12][1] = -11.57;
			level_0[12][2] = -2.61;
			level_0[12][3] = -1.34;
		}
		{	//15
			level_0[13][0] = -13.08;
			level_0[13][1] = -12.9;
			level_0[13][2] = -0.1;
			level_0[13][3] = 0.12;
		}
		{	//16
			level_0[14][0] = -12.57;
			level_0[14][1] = -12.45;
			level_0[14][2] = 2.93;
			level_0[14][3] = 3.07;
		}
		{	//17
			level_0[15][0] = -12.05;
			level_0[15][1] = -11.95;
			level_0[15][2] = 5.33;
			level_0[15][3] = 5.45;
		}
		{	//18
			level_0[16][0] = -5.39;
			level_0[16][1] = -4.61;
			level_0[16][2] = -0.21;
			level_0[16][3] = -0.12;
		}
		{	//19
			level_0[17][0] = -5.61;
			level_0[17][1] = -5.27;
			level_0[17][2] = -0.12;
			level_0[17][3] = 0.85;
		}
		{	//20
			level_0[18][0] = -5.56;
			level_0[18][1] = -2.63;
			level_0[18][2] = 0.51;
			level_0[18][3] = 1.20;
		}
		{	//21
			level_0[19][0] = -3.25;
			level_0[19][1] = -3.00;
			level_0[19][2] = -0.15;
			level_0[19][3] = 1.48;
		}
		{	//22
			level_0[20][0] = -3.88;
			level_0[20][1] = -3.25;
			level_0[20][2] = -0.19;
			level_0[20][3] = -0.13;
		}
		{	//23
			level_0[21][0] = -5.69;
			level_0[21][1] = -3.59;
			level_0[21][2] = -6.16;
			level_0[21][3] = -5.83;
		}
		{	//24
			level_0[22][0] = -8.44;
			level_0[22][1] = -5.19;
			level_0[22][2] = -0.17;
			level_0[22][3] = 6.45;
		}
		{	//25
			level_0[23][0] = -10.11;
			level_0[23][1] = -9.28;
			level_0[23][2] = -10.22;
			level_0[23][3] = -8.44;
		}

	}


	// Kolizje z pietrem 1
	
{
	{	//1 
		level_1[0][0] = -5.15;
		level_1[0][1] = -3.04;
		level_1[0][2] = 2.48;
		level_1[0][3] = 2.69;
	}
	{	//2 
		level_1[1][0] = -5.35;
		level_1[1][1] = -5.15;
		level_1[1][2] = 2.63;
		level_1[1][3] = 4.15;
	}
	{	//3
		level_1[2][0] = -8.34;
		level_1[2][1] = -5.07;
		level_1[2][2] = 4.15;
		level_1[2][3] = 4.29;
	}
	{	//4
		level_1[3][0] = -8.49;
		level_1[3][1] = -8.36;
		level_1[3][2] = 4.26;
		level_1[3][3] = 6.86;
	}
	{	//5 
		level_1[4][0] = -8.38;
		level_1[4][1] = -6.44;
		level_1[4][2] = 6.85;
		level_1[4][3] = 6.96;
	}
	{	//6
		level_1[5][0] = -6.45;
		level_1[5][1] = -6.37;
		level_1[5][2] = 6.93;
		level_1[5][3] = 11.80;
	}
	{	//7
		level_1[6][0] = -6.37;
		level_1[6][1] = -0.78;
		level_1[6][2] = 11.88;
		level_1[6][3] = 11.95;
	}
	{	//8
		level_1[7][0] = -0.80;
		level_1[7][1] = -0.70;
		level_1[7][2] = 6.55;
		level_1[7][3] = 11.88;
	}
	{	//9
		level_1[8][0] = -0.79;
		level_1[8][1] = 1.50;
		level_1[8][2] = 6.51;
		level_1[8][3] = 6.67;
	}
	{	//10
		level_1[9][0] = 1.35;
		level_1[9][1] = 1.45;
		level_1[9][2] = 6.55;
		level_1[9][3] = 11.9;
	}
	{	//11
		level_1[10][0] = 1.45;
		level_1[10][1] = 5.23;
		level_1[10][2] = 11.86;
		level_1[10][3] = 12.0;
	}
	{	//12
		level_1[11][0] = 5.21;
		level_1[11][1] = 5.30;
		level_1[11][2] = 6.68;
		level_1[11][3] = 11.89;
	}
	{	//13
		level_1[12][0] = 2.215;
		level_1[12][1] = 8.79;
		level_1[12][2] = 6.55;
		level_1[12][3] = 6.68;
	}
	{	//14
		level_1[13][0] = 8.76;
		level_1[13][1] = 8.81;
		level_1[13][2] = 4.23;
		level_1[13][3] = 6.56;
	}
	{	//15
		level_1[14][0] = 3.36;
		level_1[14][1] = 8.79;
		level_1[14][2] = 4.05;
		level_1[14][3] = 4.27;
	}
	{	//16
		level_1[15][0] = 3.39;
		level_1[15][1] = 3.47;
		level_1[15][2] = 0.22;
		level_1[15][3] = 4.23;
	}
	{	//17
		level_1[16][0] = -0.83;
		level_1[16][1] = 3.42;
		level_1[16][2] = 0.15;
		level_1[16][3] = 0.25;
	}
	{	//18
		level_1[17][0] = -0.88;
		level_1[17][1] = -0.83;
		level_1[17][2] = 0.21;
		level_1[17][3] = 4.12;
	}
	{	//19
		level_1[18][0] = -3.11;
		level_1[18][1] = 2.64;
		level_1[18][2] = 4.10;
		level_1[18][3] = 4.24;
	}
	{	//20
		level_1[19][0] = -3.04;
		level_1[19][1] = -2.90;
		level_1[19][2] = 2.58;
		level_1[19][3] = 4.16;
	}
	{	//21
		level_1[20][0] = -3.75;
		level_1[20][1] = -3.12;
		level_1[20][2] = 4.178;
		level_1[20][3] = 4.224;
	}
	{	//22
		level_1[21][0] = -5.06;
		level_1[21][1] = -4.44;
		level_1[21][2] = 4.155;
		level_1[21][3] = 4.24;
	}
	{	//23
		level_1[22][0] = -2.44;
		level_1[22][1] = -2.02;
		level_1[22][2] = 6.84;
		level_1[22][3] = 7.26;
	}
	{	//24
		level_1[23][0] = -5.05;
		level_1[23][1] = -4.63;
		level_1[23][2] = 6.84;
		level_1[23][3] = 7.26;
	}
	{	//25
		level_1[24][0] = -6.08;
		level_1[24][1] = -5.65;
		level_1[24][2] = 7.59;
		level_1[24][3] = 9.89;
	}
	{	//24
		level_1[25][0] = -4.55;
		level_1[25][1] = -2.22;
		level_1[25][2] = 11.20;
		level_1[25][3] = 11.63;
	}
	{	//24
		level_1[26][0] = -1.48;
		level_1[26][1] = -1.07;
		level_1[26][2] = 8.40;
		level_1[26][3] = 10.84;
	}
	{	//24
		level_1[27][0] = -0.74;
		level_1[27][1] = -0.66;
		level_1[27][2] = 4.21;
		level_1[27][3] = 4.98;
	}
	{	//24
		level_1[28][0] = -0.76;
		level_1[28][1] = -0.66;
		level_1[28][2] = 5.85;
		level_1[28][3] = 6.58;
	}
	{	//24
		level_1[29][0] = 3.30;
		level_1[29][1] = 5.18;
		level_1[29][2] = 6.26;
		level_1[29][3] = 6.58;
	}
	{	//24
		level_1[30][0] = 6.39;
		level_1[30][1] = 7.82;
		level_1[30][2] = 6.26;
		level_1[30][3] = 6.58;
	}
	{	//24
		level_1[31][0] = 7.09;
		level_1[31][1] = 8.08;
		level_1[31][2] = 4.22;
		level_1[31][3] = 4.54;
	}
	{	//24
		level_1[32][0] = 1.90;
		level_1[32][1] = 2.35;
		level_1[32][2] = 11.07;
		level_1[32][3] = 11.90;
	}
	{	//24
		level_1[33][0] = 2.32;
		level_1[33][1] = 2.72;
		level_1[33][2] = 7.31;
		level_1[33][3] = 11.58;
	}
	{	//24
		level_1[34][0] = 3.36;
		level_1[34][1] = 3.8;
		level_1[34][2] = 7.31;
		level_1[34][3] = 11.56;
	}
	{	//24
		level_1[35][0] = 4.41;
		level_1[35][1] = 4.81;
		level_1[35][2] = 7.32;
		level_1[35][3] = 11.57;
	}
	{	//24
		level_1[36][0] = 2.07;
		level_1[36][1] = 2.57;
		level_1[36][2] = 0.54;
		level_1[36][3] = 1.34;
	} {	//24
		level_1[37][0] = 1.7;
		level_1[37][1] = 2.09;
		level_1[37][2] = 0.24;
		level_1[37][3] = 1.68;
	} {	//24
		level_1[38][0] = 0.72;
		level_1[38][1] = 1.14;
		level_1[38][2] = 0.24;
		level_1[38][3] = 1.70;
	} {	//24
		level_1[39][0] = -0.26;
		level_1[39][1] = 0.14;
		level_1[39][2] = 0.21;
		level_1[39][3] = 1.69;
	}
	{	//24
		level_1[40][0] = -0.25;
		level_1[40][1] = 0.16;
		level_1[40][2] = 2.70;
		level_1[40][3] = 4.14;
	}
	{	//24
		level_1[41][0] = 0.71;
		level_1[41][1] = 1.14;
		level_1[41][2] = 2.72;
		level_1[41][3] = 4.13;
	}
	{	//24
		level_1[42][0] = 1.71;
		level_1[42][1] = 2.12;
		level_1[42][2] = 2.70;
		level_1[42][3] = 4.13;
	}

		 ///TU BRAKUJE
}


// Kolizje z pietrem 2

{
	{	//1 
		level_2[0][0] = -3.04;
		level_2[0][1] = -2.64;
		level_2[0][2] = 47.97;
		level_2[0][3] = 50.25;
	}
	{	//2
		level_2[1][0] = -5.24;
		level_2[1][1] = -2.97;
		level_2[1][2] = 49.69;
		level_2[1][3] = 49.87;
	}
	{	//3
		level_2[2][0] = -5.28;
		level_2[2][1] = -5.14;
		level_2[2][2] = 47.79;
		level_2[2][3] = 49.73;
	}
	{	//4 
		level_2[3][0] = -5.2;
		level_2[3][1] = -2.84;
		level_2[3][2] = 47.84;
		level_2[3][3] = 48.14;
	}



}

// Kolizje z pietrem 3 

	{
		{
			{	//1
				level_3[0][0] = -3.04;
				level_3[0][1] = -2.87;
				level_3[0][2] = 22.53;
				level_3[0][3] = 24.73;
			}
			{	//2
				level_3[1][0] = -5.47;
				level_3[1][1] = -2.98;
				level_3[1][2] = 22.82;
				level_3[1][3] = 23.15;
			}
			{	//3
				level_3[2][0] = -5.19;
				level_3[2][1] = -5.15;
				level_3[2][2] = 22.96;
				level_3[2][3] = 24.74;
			}
			{	//4
				level_3[3][0] = -8.51;
				level_3[3][1] = -5.17;
				level_3[3][2] = 24.37;
				level_3[3][3] = 24.78;
			}
			{	//5
				level_3[4][0] = -8.13;
				level_3[4][1] = -7.91;
				level_3[4][2] = 20.89;
				level_3[4][3] = 24.37;
			}
			{	//6 i 7
				level_3[5][0] = -16.18;
				level_3[5][1] = -7.96;
				level_3[5][2] = 20.66;
				level_3[5][3] = 20.89;
			}
			{	//8
				level_3[6][0] = -15.91;
				level_3[6][1] = -15.80;
				level_3[6][2] = 20.84;
				level_3[6][3] = 30.28;
			}
			{	//9
				level_3[7][0] = -15.91;
				level_3[7][1] = -10.33;
				level_3[7][2] = 30.23;
				level_3[7][3] = 30.43;
			}
			{	//10 , 38
				level_3[8][0] = -10.50;
				level_3[8][1] = -10.36;
				level_3[8][2] = 26.44;
				level_3[8][3] = 30.37;
			}
			{	//11
				level_3[9][0] = -10.39;
				level_3[9][1] = 1.52;
				level_3[9][2] = 27.08;
				level_3[9][3] = 27.21;
			}
			{	//12
				level_3[10][0] = -0.83;
				level_3[10][1] = -0.67;
				level_3[10][2] = 27.19;
				level_3[10][3] = 30.95;
			}
			{	//13
				level_3[11][0] = -0.71;
				level_3[11][1] = 2.92;
				level_3[11][2] = 30.91;
				level_3[11][3] = 31.08;
			}
			{	//14
				level_3[12][0] = 2.68;
				level_3[12][1] = 2.82;
				level_3[12][2] = 27.16;
				level_3[12][3] = 30.94;
			}
			{	//15
				level_3[13][0] = 2.08;
				level_3[13][1] = 8.81;
				level_3[13][2] = 27.08;
				level_3[13][3] = 27.21;
			}
			{	//16
				level_3[14][0] = 8.77;
				level_3[14][1] = 9.04;
				level_3[14][2] = 24.63;
				level_3[14][3] = 27.11;
			}
			{	//17, 18
				level_3[15][0] = -3.73;
				level_3[15][1] = 8.81;
				level_3[15][2] = 24.68;
				level_3[15][3] = 24.78;
			}
			{	//19
				level_3[16][0] = -5.18;
				level_3[16][1] = -4.45;
				level_3[16][2] = 24.67;
				level_3[16][3] = 24.78;
			}
			{	//20
				level_3[17][0] = -8.40;
				level_3[17][1] = -8.16;
				level_3[17][2] = 22.22;
				level_3[17][3] = 23.50;
			}
			{	//21
				level_3[18][0] = -10.40;
				level_3[18][1] = -10.01;
				level_3[18][2] = 24.35;
				level_3[18][3] = 24.74;
			}
			{	//22 , 36, 37
				level_3[19][0] = -10.50;
				level_3[19][1] = -10.37;
				level_3[19][2] = 20.81;
				level_3[19][3] = 25.88;
			}
			{	//23
				level_3[20][0] = -15.80;
				level_3[20][1] = -14.97;
				level_3[20][2] = 21.39;
				level_3[20][3] = 21.87;
			}
			{	//24
				level_3[21][0] = -15.04;
				level_3[21][1] = -11.43;
				level_3[21][2] = 22.39;
				level_3[21][3] = 22.85;
			}
			{	//25
				level_3[22][0] = -15.01;
				level_3[22][1] = -11.43;
				level_3[22][2] = 23.35;
				level_3[22][3] = 23.79;
			}
			{	//26
				level_3[23][0] = -14.31;
				level_3[23][1] = -12.15;
				level_3[23][2] = 24.24;
				level_3[23][3] = 24.68;
			}
			{	//27
				level_3[24][0] = -15.01;
				level_3[24][1] = -12.15;
				level_3[24][2] = 25.14;
				level_3[24][3] = 25.59;
			}
			{	//28
				level_3[25][0] = -15;
				level_3[25][1] = -12.15;
				level_3[25][2] = 26.1;
				level_3[25][3] = 26.54;
			}
			{	//29
				level_3[26][0] = -15.01;
				level_3[26][1] = -11.44;
				level_3[26][2] = 27.0;
				level_3[26][3] = 27.48;
			}
			{	//30
				level_3[27][0] = -11.77;
				level_3[27][1] = -11.36;
				level_3[27][2] = 24.35;
				level_3[27][3] = 24.75;
			}
			{	//31
				level_3[28][0] = -15.13;
				level_3[28][1] = -14.73;
				level_3[28][2] = 24.34;
				level_3[28][3] = 24.74;
			}
			{	//32
				level_3[29][0] = -11.77;
				level_3[29][1] = -11.35;
				level_3[29][2] = 27.78;
				level_3[29][3] = 28.18;
			}
			{	//33
				level_3[30][0] = -15.13;
				level_3[30][1] = -14.73;
				level_3[30][2] = 27.74;
				level_3[30][3] = 28.15;
			}
			{	//34
				level_3[31][0] = -14.30;
				level_3[31][1] = -12.14;
				level_3[31][2] = 27.95;
				level_3[31][3] = 28.37;
			}
			{	//35
				level_3[32][0] = -15.01;
				level_3[32][1] = -11.43;
				level_3[32][2] = 28.89;
				level_3[32][3] = 29.31;
			}
			{	//39
				level_3[33][0] = -10.49;
				level_3[33][1] = -9.82;
				level_3[33][2] = 26.38;
				level_3[33][3] = 26.46;
			}
			{	//40
				level_3[34][0] = -2.07;
				level_3[34][1] = -0.06;
				level_3[34][2] = 26.79;
				level_3[34][3] = 27.05;
			}
			{	//41
				level_3[35][0] = 0.30;
				level_3[35][1] = 0.37;
				level_3[35][2] = 26.36;
				level_3[35][3] = 27.13;
			}
			{	//42
				level_3[36][0] = 0.3;
				level_3[36][1] = 0.37;
				level_3[36][2] = 24.73;
				level_3[36][3] = 25.51;
			}
			{	//43
				level_3[37][0] = 1.99;
				level_3[37][1] = 2.09;
				level_3[37][2] = 27.08;
				level_3[37][3] = 27.63;
			}
			{	//44
				level_3[38][0] = 0.53;
				level_3[38][1] = 1.37;
				level_3[38][2] = 28.0;
				level_3[38][3] = 28.51;
			}
			{	//45
				level_3[39][0] = -0.66;
				level_3[39][1] = -0.17;
				level_3[39][2] = 28.58;
				level_3[39][3] = 30.71;
			}
			{	//46
				level_3[40][0] = 0.54;
				level_3[40][1] = 1.07;
				level_3[40][2] = 28.44;
				level_3[40][3] = 30.7;
			}
			{	//47
				level_3[41][0] = 2.11;
				level_3[41][1] = 2.67;
				level_3[41][2] = 28.68;
				level_3[41][3] = 30.93;
			}
	
		}
	}

	// Kolizje z pietrem 4
{
		//1 
		level_4[0][0] = 3.47;
		level_4[0][1] = 5.05;
		level_4[0][2] = -8.49;
		level_4[0][3] = -8.35;
		//2
		level_4[1][0] = 3.12;
		level_4[1][1] = 5.23;
		level_4[1][2] = -3.15;
		level_4[1][3] = -2.95;
		//3
		level_4[2][0] = 3.12;
		level_4[2][1] = 5.32;
		level_4[2][2] = -0.63;
		level_4[2][3] = -0.46;
		//4
		{	//4
			level_4[3][0] = -3.04;
			level_4[3][1] = -2.9;
			level_4[3][2] = -12.9;
			level_4[3][3] = -10.85;
		}
		{	//5 
			level_4[4][0] = -5.21;
			level_4[4][1] = -4.03;
			level_4[4][2] = -12.49;
			level_4[4][3] = -12.44;
		}
		{	//6
			level_4[5][0] = -5.27;
			level_4[5][1] = -5.14;
			level_4[5][2] = -12.56;
			level_4[5][3] = -10.86;
		}
		{	//7
			level_4[6][0] = -8.12;
			level_4[6][1] = -4.45;
			level_4[6][2] = -10.87;
			level_4[6][3] = -10.8;
		}
		{	//8
			level_4[7][0] = -8.13;
			level_4[7][1] = -8.09;
			level_4[7][2] = -14.76;
			level_4[7][3] = -10.82;
		}
		{	//9
			level_4[8][0] = -12.75;
			level_4[8][1] = -8.10;
			level_4[8][2] = -14.98;
			level_4[8][3] = -14.68;
		}
		{	//10
			level_4[9][0] = -12.53;
			level_4[9][1] = -12.30;
			level_4[9][2] = -14.78;
			level_4[9][3] = -7.89;
		}
		{	//11
			level_4[10][0] = -12.41;
			level_4[10][1] = -4.74;
			level_4[10][2] = -8.18;
			level_4[10][3] = -8.13;
		}
		{	//12
			level_4[11][0] = -4.81;
			level_4[11][1] = -4.73;
			level_4[11][2] = -8.17;
			level_4[11][3] = -5.96;
		}
		{	//13
			level_4[12][0] = -4.75;
			level_4[12][1] = -2.11;
			level_4[12][2] = -6.04;
			level_4[12][3] = -5.96;
		}
		{	//14
			level_4[13][0] = -2.2;
			level_4[13][1] = -2.13;
			level_4[13][2] = -8.43;
			level_4[13][3] = -5.96;
		}
		{	//15
			level_4[14][0] = -2.32;
			level_4[14][1] = 3.52;
			level_4[14][2] = -8.53;
			level_4[14][3] = -8.36;
		}
		{	//16
			level_4[15][0] = -0.35;
			level_4[15][1] = -0.27;
			level_4[15][2] = -8.41;
			level_4[15][3] = -3.04;
		}
		{	//17
			level_4[16][0] = -0.32;
			level_4[16][1] = 3.17;
			level_4[16][2] = -3.17;
			level_4[16][3] = -3.11;
		}
		{	//18
			level_4[17][0] = 3.12;
			level_4[17][1] = 3.17;
			level_4[17][2] = -3.12;
			level_4[17][3] = -0.35;
		}
		{	//19
			level_4[18][0] = -0.19;
			level_4[18][1] = 3.14;
			level_4[18][2] = -0.62;
			level_4[18][3] = -0.35;
		}
		{	//20
			level_4[19][0] = 0.09;
			level_4[19][1] = 0.39;
			level_4[19][2] = -0.41;
			level_4[19][3] = 3.29;
		}
		{	//21
			level_4[20][0] = 0.21;
			level_4[20][1] = 9.13;
			level_4[20][2] = 3.01;
			level_4[20][3] = 3.1;
		}
		{	//22
			level_4[21][0] = 8.8;
			level_4[21][1] = 9.11;
			level_4[21][2] = -0.71;
			level_4[21][3] = 3.15;
		}
		{	//23
			level_4[22][0] = 5.26;
			level_4[22][1] = 9.01;
			level_4[22][2] = -0.57;
			level_4[22][3] = -0.42;
		}
		{	//24
			level_4[23][0] = 5.27;
			level_4[23][1] = 5.35;
			level_4[23][2] = -3.13;
			level_4[23][3] = -0.49;
		}
		{	//25
			level_4[24][0] = 5.3;
			level_4[24][1] = 9.31;
			level_4[24][2] = -3.14;
			level_4[24][3] = -2.02;
		}
		{	//26
			level_4[25][0] = 8.73;
			level_4[25][1] = 8.95;
			level_4[25][2] = -11.22;
			level_4[25][3] = -3.08;
		}
		{	//27
			level_4[26][0] = 5.03;
			level_4[26][1] = 8.84;
			level_4[26][2] = -8.51;
			level_4[26][3] = -8.35;
		}
		{	//28
			level_4[27][0] = 0.32;
			level_4[27][1] = 1.46;
			level_4[27][2] = -7.49;
			level_4[27][3] = -7.22;
		}
		{	//29
			level_4[28][0] = -3.73;
			level_4[28][1] = 8.85;
			level_4[28][2] = -10.88;
			level_4[28][3] = -10.76;
		}
		{	//30
			level_4[29][0] = -8.41;
			level_4[29][1] = -8.09;
			level_4[29][2] = -13.19;
			level_4[29][3] = -11.99;
		}
		{	//31
			level_4[30][0] = -10.56;
			level_4[30][1] = -10.13;
			level_4[30][2] = -11.24;
			level_4[30][3] = -10.82;
		}
		{	//32
			level_4[31][0] = -12.40;
			level_4[31][1] = -12.12;
			level_4[31][2] = -13.21;
			level_4[31][3] = -11.96;
		}
		{	//33
			level_4[32][0] = -1.54;
			level_4[32][1] = -0.44;
			level_4[32][2] = -8.73;
			level_4[32][3] = -8.45;
		}
		{	//34
			level_4[33][0] = 0.28;
			level_4[33][1] = 0.38;
			level_4[33][2] = -9.23;
			level_4[33][3] = -8.46;
		}
		{	//35
			level_4[34][0] = 0.30;
			level_4[34][1] = 0.37;
			level_4[34][2] = -10.84;
			level_4[34][3] = -10.07;
		}
		{	//36
			level_4[35][0] = 3.11;
			level_4[35][1] = 3.52;
			level_4[35][2] = -8.75;
			level_4[35][3] = -8.43;
		}
		{	//37
			level_4[36][0] = 5.2;
			level_4[36][1] = 7.85;
			level_4[36][2] = -8.39;
			level_4[36][3] = -8.17;
		}
		{	//38
			level_4[37][0] = 2.23;
			level_4[37][1] = 3.41;
			level_4[37][2] = -8.41;
			level_4[37][3] = -8.18;
		}
		{	//39
			level_4[38][0] = -0.3;
			level_4[38][1] = 1.78;
			level_4[38][2] = -8.41;
			level_4[38][3] = -8.2;
		}
		//40
		level_4[39][0] = -0.31;
		level_4[39][1] = 1.74;
		level_4[39][2] = -7.92;
		level_4[39][3] = -7.45;
		//41
		level_4[40][0] = 0.82;
		level_4[40][1] = 1.3;
		level_4[40][2] = -6.54;
		level_4[40][3] = -5.5;
		//42
		level_4[41][0] = 0.11;
		level_4[41][1] = 0.93;
		level_4[41][2] = -6.37;
		level_4[41][3] = -5.68;
		//43
		level_4[42][0] = -0.31;
		level_4[42][1] = 0.22;
		level_4[42][2] = -6.54;
		level_4[42][3] = -5.51;
		//44
		level_4[43][0] = 2.89;
		level_4[43][1] = 4.08;
		level_4[43][2] = -6.62;
		level_4[43][3] = -5.44;
		//45
		level_4[44][0] = 5.92;
		level_4[44][1] = 7.54;
		level_4[44][2] = -7.21;
		level_4[44][3] = -6.6;
		//46
		level_4[45][0] = 5.34;
		level_4[45][1] = 5.96;
		level_4[45][2] = -6.64;
		level_4[45][3] = -5.05;
		//47
		level_4[46][0] = 6.48;
		level_4[46][1] = 7.0;
		level_4[46][2] = -6.2;
		level_4[46][3] = -5.33;
		//48
		level_4[47][0] = 5.84;
		level_4[47][1] = 7.4;
		level_4[47][2] = -5.07;
		level_4[47][3] = -4.37;
		//49
		level_4[48][0] = 2.9;
		level_4[48][1] = 5.52;
		level_4[48][2] = -4.0;
		level_4[48][3] = -3.78;
		//50
		level_4[49][0] = 0.02;
		level_4[49][1] = 1.68;
		level_4[49][2] = -3.37;
		level_4[49][3] = -3.12;
		//51
		level_4[50][0] = 7.98;
		level_4[50][1] = 8.26;
		level_4[50][2] = -0.48;
		level_4[50][3] = 1.39;
		//52
		level_4[51][0] = 6.87;
		level_4[51][1] = 8.12;
		level_4[51][2] = 2.26;
		level_4[51][3] = 2.54;
		//53
		level_4[52][0] = 4.02;
		level_4[52][1] = 5.29;
		level_4[52][2] = 2.25;
		level_4[52][3] = 2.54;
		//54
		level_4[53][0] = 1.71;
		level_4[53][1] = 2.3;
		level_4[53][2] = 2.29;
		level_4[53][3] = 2.55;
		//55
		level_4[54][0] = 1.88;
		level_4[54][1] = 2.03;
		level_4[54][2] = 2.13;
		level_4[54][3] = 2.32;
		//56
		level_4[55][0] = 0.88;
		level_4[55][1] = 1.16;
		level_4[55][2] = 1.01;
		level_4[55][3] = 1.6;
}

}