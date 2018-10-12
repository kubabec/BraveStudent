#include "vec3.h"
#include "Tree.h"
#include "Model3D.h"

Tree::Tree(Model3D* model, vec3 pos, vec3 scale, int rotation) {
	this->model = model;
	this->pos = pos;
	this->scale = scale;
	this->rotation = rotation;

}

Tree::~Tree() {

}

void Tree::Render()
{

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


void Tree::Update()
{

}