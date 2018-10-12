#pragma once
#include "GL\freeglut.h"
#include "SceneObject.h"
#include "Model3D.h"
#include <vector>

class Fire : public SceneObject {
public:
	Fire(Model3D** model, vec3 pos, vec3 scale,int starter, int rotation);
	~Fire();
	void Render();
	void Update();
	Model3D** model;
	vec3 pos;
	vec3 scale;
	int fire_counter;
	int rotation;
	int framecounter;
};
