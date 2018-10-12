#include "vec3.h"
#include "Reward.h"
#include "Model3D.h"
#include "rotation.h"


Reward::Reward(Model3D* model, vec3 pos, vec3 scale, Player* player, int type) {
	this->model = model;
	this->pos = pos;
	this->scale = scale;
	this->player = player;
	rotation = rand() % 10;
	resize = 0;
	resizeFlag = true;
	isHeldByPlayer = false; 
	this->RewardType = type;
	isCompleted = false; 
	OnCarPlace = vec3(-10, 0.52, -9.2);


	switch (RewardType) {
	case 1 :
		this->value = 1250;
		break;
	case 2:
		this->value = 2599;
		break;
	case 3:
		this->value = 499;
		break;
	case 4:
		this->value = 735;
		break;
	}
}

Reward::~Reward() {

}

void Reward::Render(){
	float mat_ambient2[] = { 0.7, 0.7, 0.7 };
	float mat_diffuse2[] = { .6, 0.6,0.6 };
	float mat_specular2[] = { 0.6, 0.6,0.6 };


	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
	if (!isCompleted) {
		if (isHeldByPlayer) {
			this->pos.x = player->pos.x + player->dir.x*0.005;
			this->pos.y = player->pos.y-0.01;
			this->pos.z = player->pos.z + player->dir.z*0.005;

			float iloczynSkalarny = player->dir.x * 1;
			float angle = acos(iloczynSkalarny / sqrt(pow(player->dir.x, 2) + pow(player->dir.z, 2)));
			if (player->dir.z < 0)
				rotation = angle*(180 / PI);
			else
				rotation = -angle*(180 / PI);
//
		}


		if (!isHeldByPlayer) {

		//		pos = vec3(-9.97, 0.54, -9.2);
			this->rotation += 1;
			float maxResize;
			float resizeRatio;

			if (RewardType > 1) {
				maxResize = 0.02;
				resizeRatio = 0.0005;
			}
			else {
				maxResize = 0.1;
				resizeRatio = 0.005;
			}


			if (this->rotation > 360)	this->rotation = 0;


			if (this->resize < maxResize && resizeFlag)
				this->resize += resizeRatio;
			else
				resizeFlag = false;

			if (this->resize > 0 && !resizeFlag)
				this->resize -= resizeRatio;
			else
				resizeFlag = true;

		}

		glPushMatrix();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, model->TeksturaModelu->getID());

		glTranslatef(this->pos.x, this->pos.y, this->pos.z);
		glRotatef(rotation, 0.f, 1.f, 0.f);
		glRotatef(180, 0.f, 1.f, 0.f);

		if (isHeldByPlayer) {
			glScalef(this->scale.x*0.15, this->scale.y*0.15, this->scale.z*0.15);
		}
		else
			glScalef(this->scale.x + resize, this->scale.y + resize, this->scale.z + resize);

		glCallList(model->ModelID);

		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
	else if(isCompleted){ // Zostalo doniesione na miejsce 
	
		pos = OnCarPlace;
	//	printf("%d", OnCarPlace.x);
		//printf("%d", OnCarPlace.y);
	//	printf("%d", OnCarPlace.y);
		glPushMatrix();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, model->TeksturaModelu->getID());

		glTranslatef(this->pos.x, this->pos.y, this->pos.z);
		glRotatef(rotation, 0.f, 1.f, 0.f);
		glRotatef(180, 0.f, 1.f, 0.f);
		glRotatef(160, 0.f, 0.f, 1.f);
	//	glRotatef(180, 1.f, 0.f, 0.f);
		glScalef(this->scale.x, this->scale.y, this->scale.z);
		
		
		glCallList(model->ModelID);

		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
	float mat_ambient22[] = { 0.7, 0.7, 0.7 };
	float mat_diffuse22[] = { .6, 0.6,0.6 };
	float mat_specular22[] = { 0.6, 0.6,0.6 };


	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient22);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse22);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular22);
}


void Reward::Update()
{

}




