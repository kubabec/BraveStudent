#pragma once
#include "GL\freeglut.h"

class Tekstura {
public:

	Tekstura(char* filename);
	~Tekstura();
	GLuint getID();

	GLuint ID;
	

};