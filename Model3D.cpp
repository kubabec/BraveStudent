#include "vec3.h"
#include "Model3D.h"



Model3D::Model3D(char* tekstura)
{

	this->TeksturaModelu = new Tekstura(tekstura);
	//this->pos = pos;
	//this->color = color;
	//this->scale = scale;
}


Model3D::~Model3D()
{
	printf("Dekstruktor tekstury");
	glDeleteLists(ModelID, 10);
	delete TeksturaModelu;

}	    

bool Model3D::load(std::string filename)
{
	FILE * fp = fopen(filename.c_str(), "r");

	if (fp == NULL) {
		printf("Nie wczytano pliku %s\n", filename.c_str());
		return false;
	}

	struct SFace {
		int v[3];
		int n[3];
		int t[3];
	};

	vertices.clear();
	std::vector<vec3> loaded_vertices;
	std::vector<SFace> loaded_faces;
	std::vector<vec3> loaded_vn;
	std::vector<vec3> loaded_vt;
	char buf[256];

	while (fgets(buf, 256, fp)) {
		if (buf[0] == 'v' && buf[1] == ' ') {
			vec3 vertex;
			sscanf(buf, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
			loaded_vertices.push_back(vertex);
		}
		if (buf[0] == 'v' && buf[1] == 't') {
			vec3 vt;	
			sscanf(buf, "vt %f %f %f", &vt.x, &vt.y, &vt.z);
			loaded_vt.push_back(vt);
			}

		if (buf[0] == 'v' && buf[1] == 'n') {
			vec3 vn;
			sscanf(buf, "vn %f %f %f", &vn.x, &vn.y, &vn.z);
			loaded_vn.push_back(vn);
		} 
		if (buf[0] == 'f' && buf[1] == ' ') {
			SFace face;
				sscanf(buf, "f %d/%d/%d %d/%d/%d %d/%d/%d", &face.v[0], &face.t[0], &face.n[0], &face.v[1], &face.t[1], &face.n[1], &face.v[2], &face.t[2], &face.n[2] );
			loaded_faces.push_back(face);
		}
	}

	fclose(fp);

	for (int i = 0; i < loaded_faces.size(); ++i) {
		for (int j = 0; j < 3; ++j) {
			vertices.push_back(loaded_vertices[loaded_faces[i].v[j] - 1]);
			VT.push_back(loaded_vt[loaded_faces[i].t[j] - 1]);
			VN.push_back(loaded_vn[loaded_faces[i].n[j] - 1]);	
		}
	}

	ModelID = glGenLists(1);
	glNewList(ModelID, GL_COMPILE);

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < vertices.size(); i++) {
		glNormal3f(VN[i].x, VN[i].y, VN[i].z);
		glTexCoord2f(VT[i].x, VT[i].y);
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	}
	glEnd();

	glEndList();

	return true;
}

void Model3D::Render()
{
	float mat_ambient2[] = { 1, 1,1 };
	float mat_diffuse2[] = { 0, 0,0 };
	float mat_specular2[] = { 1, 1,1 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);


}

void Model3D::Update()
{
	//glDeleteLists(ModelID, 1);
}