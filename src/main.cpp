#include <GL/glut.h>
#include "ObjParser.h"
#include <stdio.h>
#include <iostream>

using namespace std;

void DoDisplay();
void DoKeyboard(unsigned char key, int x, int y);
GLfloat xAngle, yAngle, zAngle;
ObjParser p;

int main(int argc, char** argv)
{
	p.load("box/box.obj");
	glutInit(&argc, argv);
	
	glutCreateWindow("OpenGL");
	glutDisplayFunc(DoDisplay);
	glutKeyboardFunc(DoKeyboard);
	p.loadTexture("box/box.bmp");
	
	
	glutMainLoop();
	return 0;
}

void DoKeyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':yAngle += 2; break;
	case 'd':yAngle -= 2; break;
	case 'w':xAngle += 2; break;
	case 's':xAngle -= 2; break;
	case 'q':zAngle += 2; break;
	case 'e':zAngle -= 2; break;
	case 'z':xAngle = yAngle = zAngle = 0.0; break;
	}
	char info[128];
	sprintf(info, "x=%.1f, y=%.1f, z=%.1f", xAngle, yAngle, zAngle);
	glutSetWindowTitle(info);
	glutPostRedisplay();
}

void DoDisplay()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glScalef(0.5f, 0.5f, 0.5f);
	glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
	glRotatef(zAngle, 0.0f, 0.0f, 1.0f);


	glEnableClientState(GL_VERTEX_ARRAY); 
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	//glVertexPointer(3, GL_FLOAT, 0, vert);

	p.draw();
	//glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, index);

	glPopMatrix();
	glFlush();
}