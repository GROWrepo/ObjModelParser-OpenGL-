#include "ObjParser.h"
#include <fstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>


ObjParser::ObjParser()
{
}


ObjParser::~ObjParser()
{
}

void ObjParser::load(char* filename)
{
	ifstream openFile(filename);
	char buffer[100];
	memset(buffer, 0, 100);
	if (openFile.is_open()) {
		while (!openFile.eof()) {
			openFile.getline(buffer, 100);
			input(buffer);
		}
	}
	else {
		cout << "load file fail" << endl;
	}
	
}

void ObjParser::input(char* buffer)
{
	if (memcmp(buffer, "v ", 2) == 0) {
		float v1, v2, v3;
		sscanf(buffer, "v %f %f %f", &v1, &v2, &v3);
		this->vertex.push_back(Vector3(v1, v2, v3));
	}
	else if (memcmp(buffer, "vn ", 3) == 0) {
		float v1, v2, v3;
		sscanf(buffer, "vn %f %f %f", &v1, &v2, &v3);
		this->normal.push_back(Vector3(v1, v2, v3));

	}
	else if (memcmp(buffer, "vt ", 3) == 0) {
		float v1, v2, v3;
		sscanf(buffer, "vt %f %f %f", &v1, &v2, &v3);
		this->tex.push_back(Vector3(v1, v2, v3));
	}

	else if (memcmp(buffer, "s ", 2) == 0) {

	}
	else if (memcmp(buffer, "f ", 2) == 0) {
		unsigned int v[4], uv[4], nv[4];
		sscanf(buffer, "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d"
			, &v[0], &uv[0], &nv[0]
			, &v[1], &uv[1], &nv[1]
			, &v[2], &uv[2], &nv[2]
			, &v[3], &uv[3], &nv[3]);
		static int arr[] = { 1, 2, 3, 1, 3, 0 };
		for (int i = 0; i < 6; i++) {
			this->realVertex.push_back(vertex[v[arr[i]] - 1]);
			this->realTex.push_back(tex[uv[arr[i]] - 1]);
			this->realNormal.push_back(normal[nv[arr[i]] - 1]);
			//for (int i = 0; i < 3; i++) {
			//	this->realVertex.push_back(vertex[3 * (v[arr[i]] - 1) + i]);
			//	this->realTex.push_back(tex[3 * (uv[arr[i]] - 1) + i]);
			//}

			this->vIndices.push_back(v[arr[i]] - 1);
		}
		/*
		this->vIndices.push_back(v[1] - 1);
		this->vIndices.push_back(v[2] - 1);
		this->vIndices.push_back(v[3] - 1);

		cout << v[1] - 1 << ", " << v[2] - 1 << ", " << v[3] - 1 << endl;

		this->vIndices.push_back(v[1] - 1);
		this->vIndices.push_back(v[3] - 1);
		this->vIndices.push_back(v[0] - 1);

		cout << v[1] - 1 << ", " << v[3] - 1 << ", " << v[0] - 1 << endl;
		*/
	}

	else if (memcmp(buffer, "g ", 2) == 0) {

	}
	else if (memcmp(buffer, "mtllib ", 7) == 0) {

	}
	else if (memcmp(buffer, "usemtl ", 7) == 0) {

	}
}


void ObjParser::draw()
{
	//glBegin(GL_POLYGON);
	GLubyte* indices = &vIndices[0];
	float* v = (float*)&vertex[0];//&realVertex[0];//&vertex[0];
	float* t = (float*)&realTex[0];
	float* n = (float*)&realNormal[0];
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexCoordPointer(3, GL_FLOAT, 0, t);
	glNormalPointer(GL_FLOAT, 0, n);

	//glVertexPointer(3, GL_FLOAT, 0, v);
	//glDrawElements(GL_TRIANGLES, vIndices.size(), GL_UNSIGNED_BYTE, indices);

	glVertexPointer(3, GL_FLOAT, 0, &realVertex[0]);
	glDrawArrays(GL_TRIANGLES, 0, realVertex.size());
	//glEnd();
}

bool ObjParser::loadTexture(char * filename)
{
	IplImage *img = cvLoadImage (filename);
	if (!img) return false;

	cvFlip (img, img);

	glGenTextures (1, &this->texture);
	glBindTexture (GL_TEXTURE_2D, this->texture);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D (GL_TEXTURE_2D, 0, 3, img->width, img->height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, img->imageData);
	cout << "texture number : " << texture << endl;
	cvReleaseImage (&img);
	return true;

}