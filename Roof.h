#pragma once
#include "GL\freeglut.h"
#include "SceneObject.h"
#include "Model3D.h"
#include <vector>

class Roof : public SceneObject {
public:
	Roof(Model3D* model, vec3 pos, vec3 scale, int rotation);
	~Roof();
	void Render();
	void Update();
	Model3D* model;
	vec3 pos;
	vec3 scale;
	int rotation;
};
