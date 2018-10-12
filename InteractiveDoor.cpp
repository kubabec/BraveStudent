#include "vec3.h"
#include "InteractiveDoor.h"
#include "Model3D.h"

InteractiveDoor::InteractiveDoor(Model3D* model, vec3 pos, vec3 scale, int rotation, int DoorType) {
	this->model = model;
	this->pos = pos;
	this->scale = scale;
	this->rotation = rotation;

	this->isOpened = false;
	this->DoorType = DoorType;

	this->keepOpen = false;
	this->openAngle = 0; 
	this->openDirection = 1;

}

InteractiveDoor::~InteractiveDoor() {

}

void InteractiveDoor::Render()
{

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, model->TeksturaModelu->getID());

	if(DoorType == 1 )
		glTranslatef(this->pos.x, this->pos.y + openAngle, this->pos.z);

	if (DoorType == 2)
		glTranslatef(this->pos.x, this->pos.y + (-1*openAngle), this->pos.z);
		
	if (DoorType == 3)
		glTranslatef(this->pos.x - openAngle, this->pos.y , this->pos.z);
		
	if (DoorType == 4)
		glTranslatef(this->pos.x + openAngle, this->pos.y , this->pos.z);


	

	if (keepOpen == true && isOpened == false ) {
		openAngle = openAngle - 0.02;
		if (openAngle < -1) {
			isOpened = true;
		}
	}
	if (keepOpen == false && openAngle < 0 ) {
		openAngle = openAngle + 0.02;
		if (openAngle >= 0) {
			isOpened = false;
		}
	}

	glRotatef((float)rotation*1.f, 0.f, 1.f, 0.f);
	glScalef(this->scale.x, this->scale.y, this->scale.z);
	glCallList(model->ModelID);


	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}


void InteractiveDoor::Update()
{

}