#pragma once
#include "GL\freeglut.h"
#include "SceneObject.h"
#include "Model3D.h"
#include <vector>

class Gorka : public SceneObject {
public:
	Gorka(Model3D* model, vec3 pos, vec3 scale, int rotation);
	~Gorka();
	void Render();
	void Update();
	Model3D* model;
	vec3 pos;
	vec3 scale;
	int rotation;
};
