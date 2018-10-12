#include "vec3.h"
#include "Sphere.h"
#include <iostream>


Sphere::Sphere(void)
{
}


Sphere::~Sphere(void)
{
}

void Sphere::Render()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.f, glutGet(GLUT_WINDOW_HEIGHT), -1.0, 10.0); 
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_CULL_FACE);
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//glClear(GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos2f(((float)glutGet(GLUT_WINDOW_WIDTH)) / 2, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2);
	const char* inviolableText = "Loading ... ";
	std::cout << inviolableText << std::endl;
	int inviolableLen = strlen(inviolableText);
	for (int i = 0; i < inviolableLen; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, inviolableText[i]);
	}
	glPopMatrix();


	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_CULL_FACE);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

void Sphere::Update()
{
}