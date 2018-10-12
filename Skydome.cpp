#include "vec3.h"
#include "Skydome.h"
#include "Model3D.h"

Skydome::Skydome(Model3D* model, vec3 pos, vec3 scale, float rotation) {
	this->model = model;
	this->pos = pos;
	this->scale = scale;
	this->rotation = 50;

}

Skydome::~Skydome() {

}

void Skydome::Render()
{
	float mat_ambient[] = { 1.0f, 1.0f, 1.0f };
	float mat_diffuse[] = { 1, 1, 1 };
	float mat_specular[] = { 1.f, 1.f, 1.f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, model->TeksturaModelu->getID());

	glTranslatef(this->pos.x, this->pos.y, this->pos.z);

	glRotatef(rotation, 0.0f, 1.f, 0.f);


	glScalef(this->scale.x, this->scale.y, this->scale.z);
	glCallList(model->ModelID);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	float mat_ambient2[] = { 0.3f, 0.3f,0.3f };
	float mat_diffuse2[] = { 0.3f, 0.3f,0.3f };
	float mat_specular2[] = { 0.3f, 0.3f,0.3f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
}


void Skydome::Update()
{
	this->rotation += 0.01;
	this->Render();
}