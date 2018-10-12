#pragma once
#include "SceneObject.h"
#include "Tekstura.h"
#include "GL\freeglut.h"
#include <vector>

//
// Klasa pozwalaj¹ca wczytanie obiektu 3D w postaci pliku OBJ.
// Takie pliki mo¿na wygenerowaæ w popularnych programach do tworzenia modeli 3D, np. Blender
// Polecana alternatywa : ASSIMP


class Model3D :
	public SceneObject
{
public:

	Model3D(char* tekstura);
	~Model3D();
	bool load(std::string filepath);
	void Render();
	void Update();
	Tekstura* TeksturaModelu;
	
	GLuint ModelID;
	std::vector<vec3> vertices;
	std::vector<vec3> VT;
	std::vector<vec3> VN;

};

