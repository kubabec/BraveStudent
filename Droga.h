#pragma once
#include "GL\freeglut.h"
#include "SceneObject.h"
#include "Model3D.h"
#include <vector>

class Droga : public SceneObject {
public:
	Droga(Model3D* model, vec3 pos, vec3 scale, int rotation);
	~Droga();
	void Render();
	void Update();
	Model3D* model;
	vec3 pos;
	vec3 scale;
	int rotation;
};
