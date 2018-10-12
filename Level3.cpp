#include "vec3.h"
#include "Level3.h"
#include "Model3D.h"

Level3::Level3(Model3D* model, vec3 pos, vec3 scale, int rotation) {
	this->model = model;
	this->pos = pos;
	this->scale = scale;
	this->rotation = rotation;



}

Level3::~Level3() {

}

void Level3::Render()
{
	float mat_ambient2[] = { 0.7, 0.7, 0.7 };
	float mat_diffuse2[] = { .6, 0.6,0.6 };
	float mat_specular2[] = { 0.6, 0.6,0.6 };


	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, model->TeksturaModelu->getID());

	glTranslatef(this->pos.x, this->pos.y, this->pos.z);
	glRotatef((float)rotation*1.f, 0.f, 1.f, 0.f);
	glScalef(this->scale.x, this->scale.y, this->scale.z);
	glCallList(model->ModelID);


	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}


void Level3::Update()
{

}