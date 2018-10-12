#pragma once
#include "GL\freeglut.h"
#include "SceneObject.h"
#include "Model3D.h"
#include <vector>

class Tree : public SceneObject {
public:
	Tree(Model3D* model, vec3 pos, vec3 scale, int rotation);
	~Tree();
	void Render();
	void Update();
	Model3D* model;
	vec3 pos;
	vec3 scale;
	int rotation;
};
