#pragma once
#include "GL\freeglut.h"
#include "SceneObject.h"
#include "Model3D.h"
#include <vector>

class Chodnik : public SceneObject {
public:
	Chodnik(Model3D* model, vec3 pos, vec3 scale, int rotation);
	~Chodnik();
	void Render();
	void Update();
	Model3D* model;
	vec3 pos;
	vec3 scale;
	int rotation;
};
