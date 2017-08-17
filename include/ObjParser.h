#pragma once
#include "util.h"
#include <vector>
#include <GL/glut.h>

using namespace std;

struct Vector3;
struct Material;
struct Group;

class ObjParser
{
private:
	vector<Vector3> vertex, normal, tex;
	vector<Group*> groups;
	vector<Material*> materials;
	Group* current;
	Material* curMat;
	
	GLuint texture;
public:
	ObjParser();
	~ObjParser();
	void load(char* filename);
	void input(char* buffer);
	void draw();
	bool loadTexture(char* filename);
	void loadMaterial(char* filename);
	void matInput(char* buffer);
};

struct Vector3 {
	GLfloat x, y, z;
	Vector3(GLfloat x, GLfloat y, GLfloat z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

struct Material {
	char name[256];
	int illum;
	char map_Kd[256];
	float Ns;
	float Ni;
	float d;
	float Tr;
	float Ka[3];
	float Kd[3];
	float Ks[3];
	float Tf[3];
};

struct Group {
	vector<Vector3> vertex, tex, normal;
	Material* mat;
	char name[20];
};