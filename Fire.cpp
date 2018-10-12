#include "vec3.h"
#include "Fire.h"
#include "Model3D.h"

Fire::Fire(Model3D** model, vec3 pos, vec3 scale, int starter, int rotation) {
	this->model = model;
	this->pos = pos;
	this->scale = scale;
	framecounter = 0;
	fire_counter = starter;
	this->rotation = rotation;
}

Fire::~Fire() {

}

void Fire::Render()
{
	
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, model[fire_counter]->TeksturaModelu->getID());
	
	glTranslatef(this->pos.x, this->pos.y, this->pos.z);
	glRotatef((float)rotation, 0.f, 1.f, 0.f);
	glScalef(this->scale.x, this->scale.y, this->scale.z);
	glCallList(model[fire_counter]->ModelID);


	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}


void Fire::Update()
{
	framecounter += 1;

	if (framecounter > 2) {
		if (fire_counter != 7)
			fire_counter += 1;
		else
			fire_counter = 0;

		framecounter = 0;
	}
	this->Render();
}