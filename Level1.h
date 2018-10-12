#pragma once
#include "GL\freeglut.h"
#include "SceneObject.h"
#include "Model3D.h"
#include <vector>

class Level1 : public SceneObject {
public:
	Level1(Model3D* model, vec3 pos, vec3 scale, int rotation);
	~Level1();
	void Render();
	void Update();
	Model3D* model;
	vec3 pos;
	vec3 scale;
	int rotation;


};
#pragma once
