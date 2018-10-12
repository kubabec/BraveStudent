#pragma once
#include "GL\freeglut.h"
#include "SceneObject.h"
#include "Model3D.h"
#include <vector>

class Trawa : public SceneObject {
public:
	Trawa(Model3D* model, vec3 pos, vec3 scale, int rotation);
	~Trawa();
	void Render();
	void Update();
	Model3D* model;
	vec3 pos;
	vec3 scale;
	int rotation;
};
