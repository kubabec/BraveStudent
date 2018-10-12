#pragma once
#include "GL\freeglut.h"
#define PI 3.14159265359

class SceneObject
{
public:
	SceneObject(void);
	~SceneObject(void);

	vec3 pos;

	virtual void Render() = 0;
	virtual void Update() = 0;
};

