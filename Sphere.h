#pragma once
#include "GL\freeglut.h"
#include "SceneObject.h"

// Przykład obiektu sceny dziedziczącej po klasie SceneObject - w tym wypadku sfera

class Sphere : public SceneObject
{
public:
	Sphere(void);
	~Sphere(void);

	void Render();
	void Update();

	vec3 color;
	float radius;
};

