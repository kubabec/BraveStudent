#pragma once
#include "GL\freeglut.h"
#include "SceneObject.h"
#include "Model3D.h"
#include <vector>

class Building : public SceneObject {
public:
	Building(Model3D* model, vec3 pos, vec3 scale, int rotation);
	~Building();
	void Render();
	void Update();
	Model3D* model;
	vec3 pos;
	vec3 scale;
	int rotation;
};
