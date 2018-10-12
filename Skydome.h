#pragma once
#include "GL\freeglut.h"
#include "SceneObject.h"
#include "Model3D.h"
#include <vector>

class Skydome : public SceneObject {
public:
	Skydome(Model3D* model, vec3 pos, vec3 scale, float rotation);
	~Skydome();
	void Render();
	void Update();
	Model3D* model;
	vec3 pos;
	vec3 scale;
	float rotation;
};
