#pragma once
#include "GL\freeglut.h"
#include "SceneObject.h"
#include "Model3D.h"
#include <vector>

class Porsche : public SceneObject {
public:
	Porsche(Model3D* model, vec3 pos, vec3 scale, int rotation);
	~Porsche();
	void Render();
	void Update();
	Model3D* model;
	vec3 pos;
	vec3 scale;
	int rotation;
};
