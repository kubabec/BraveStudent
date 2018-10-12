#pragma once
#include "GL\freeglut.h"
#include "SceneObject.h"
#include "Model3D.h"
#include <vector>

class InteractiveDoor : public SceneObject {
public:
	InteractiveDoor(Model3D* model, vec3 pos, vec3 scale, int rotation, int DoorType);
	~InteractiveDoor();
	void Render();
	void Update();
	Model3D* model;
	vec3 pos;
	vec3 scale;
	int rotation;
	bool isOpened;
	bool keepOpen;
	bool openDirection;
	float openAngle;
	int DoorType;

};
#pragma once
