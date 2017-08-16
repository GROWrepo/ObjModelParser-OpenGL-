#pragma once
#include <vector>
#include <GL/glut.h>

using namespace std;

struct Vector3 {
	GLfloat x, y, z;
	Vector3(GLfloat x, GLfloat y, GLfloat z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};
struct Vector2 {
	GLfloat x, y, z;
	Vector2(GLfloat x, GLfloat y) {
		this->x = x;
		this->y = y;
	}
};
class ObjParser
{
private:
	vector<Vector3> vertex, normal, tex;
	vector<GLubyte> vIndices;
	vector<Vector3> realVertex, realTex, realNormal;
	GLuint texture;
public:
	ObjParser();
	~ObjParser();
	void load(char* filename);
	void input(char* buffer);
	void draw();
	bool loadTexture(char* filename);
};

