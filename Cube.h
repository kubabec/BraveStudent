#pragma once
#include "SceneObject.h"
class Cube :
	public SceneObject
{
public:
	Cube(vec3 pos, vec3 color, float size);
	~Cube();

	void Render();
	void Update();

	vec3 color;
	float size;
};
