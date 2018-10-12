#include "vec3.h"
#include "Cube.h"


Cube::Cube(vec3 pos, vec3 color, float size)
{
	this->pos = pos;
	this->color = color;
	this->size = size;
}


Cube::~Cube()
{
}

void Cube::Render()
{

		glColor3f(0.f, 0.1f, 0.f);
		glDisable(GL_LIGHTING);
		glPushMatrix();

		glTranslatef(pos.x, pos.y, pos.z);

		glBegin(GL_QUADS);

		// dolna œciana
		glVertex3f(size / 2, -size / 2, -size / 2);
		glVertex3f(size / 2, -size / 2, size / 2);
		glVertex3f(-size / 2, -size / 2, size / 2);
		glVertex3f(-size / 2, -size / 2, -size / 2);

		// górna œciana
		glVertex3f(-size / 2, size / 2, -size / 2);
		glVertex3f(-size / 2, size / 2, size / 2);
		glVertex3f(size / 2, size / 2, size / 2);
		glVertex3f(size / 2, size / 2, -size / 2);

		// lewa œciana
		glVertex3f(-size / 2, -size / 2, -size / 2);
		glVertex3f(-size / 2, -size / 2, size / 2);
		glVertex3f(-size / 2, size / 2, size / 2);
		glVertex3f(-size / 2, size / 2, -size / 2);

		// prawo œciana
		glVertex3f(size / 2, size / 2, -size / 2);
		glVertex3f(size / 2, size / 2, size / 2);
		glVertex3f(size / 2, -size / 2, size / 2);
		glVertex3f(size / 2, -size / 2, -size / 2);

		// tylna œciana
		glVertex3f(-size / 2, size / 2, -size / 2);
		glVertex3f(size / 2, size / 2, -size / 2);
		glVertex3f(size / 2, -size / 2, -size / 2);
		glVertex3f(-size / 2, -size / 2, -size / 2);

		// przednia œciana
		glVertex3f(size / 2, size / 2, size / 2);
		glVertex3f(-size / 2, size / 2, size / 2);
		glVertex3f(-size / 2, -size / 2, size / 2);
		glVertex3f(size / 2, -size / 2, size / 2);

		glEnd();

		glPopMatrix();
		glEnable(GL_LIGHTING);
	

}

void Cube::Update()
{

}