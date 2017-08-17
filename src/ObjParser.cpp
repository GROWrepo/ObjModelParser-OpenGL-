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
  current = 0;
}


ObjParser::~ObjParser()
{
  for(int i = 0; i < groups.size(); i++) {
    Group* g = groups[i];
    g->vertex.clear();
    g->tex.clear();
    g->normal.clear();
    delete g;
  }
  groups.clear();
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
	if(current) groups.push_back(current);
	vertex.clear();
	tex.clear();
	normal.clear();
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
			current->vertex.push_back(vertex[v[arr[i]] - 1]);
			current->tex.push_back(tex[uv[arr[i]] - 1]);
			current->normal.push_back(normal[nv[arr[i]] - 1]);
		}
	}

	else if (memcmp(buffer, "g ", 2) == 0) {
		if(current) {
		  groups.push_back(current);
		}
		current = new Group();
		sscanf(buffer, "g %s", current->name);
	}
	else if (memcmp(buffer, "mtllib ", 7) == 0) {
		char filename[20];
		cout << "mtllib" << endl;
		sscanf(buffer, "mtllib %s", filename);
		sprintf(buffer, "box/%s", filename);
		loadMaterial(buffer);
	}
	else if (memcmp(buffer, "usemtl ", 7) == 0) {
		cout << buffer << endl;
		char temp[20];
		sscanf(buffer, "usemtl %s", temp);
		for(int i = 0; i < materials.size(); i++) {
		      if(strcmp(materials[i]->name, temp)) {
			  current->mat = materials[i];
			  break;
		      }
		}
	}
}


void ObjParser::draw()
{
	for(int i = 0; i < groups.size(); i++) {
		Group* g = groups[i];
		float* v = (float*)&g->vertex[0];
		float* t = (float*)&g->tex[0];
		float* n = (float*)&g->normal[0];
		
		//glColor3f (g->mat->Kd[0], g->mat->Kd[1], g->mat->Kd[2]);
		
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexCoordPointer(3, GL_FLOAT, 0, t);
		glNormalPointer(GL_FLOAT, 0, n);

		glVertexPointer(3, GL_FLOAT, 0, v);
		glDrawArrays(GL_TRIANGLES, 0, g->vertex.size());
	}
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

void ObjParser::loadMaterial(char* filename) {
	ifstream openFile(filename);
	char buffer[100];
	memset(buffer, 0, 100);
	if (openFile.is_open()) {
		while (!openFile.eof()) {
			openFile.getline(buffer, 100);
			matInput(buffer);
		}
	}
	else {
		cout << "load material file fail" << endl;
	}
}

void ObjParser::matInput(char* buffer) {
	if(memcmp(buffer, "newmtl ", 7) == 0) {
		if(curMat) {
		    materials.push_back(curMat);
		}
		curMat = new Material();
		
		sscanf(buffer, "newmtl %s", curMat->name);
	}
	else if(memcmp(buffer, "Ns ", 3) == 0) {
		sscanf(buffer, "Ns %f", &curMat->Ns);
	}
	else if(memcmp(buffer, "d ", 2) == 0) {
		sscanf(buffer, "d %f", &curMat->d);
	}
	else if(memcmp(buffer, "Tr ", 3) == 0) {
		sscanf(buffer, "Tr %f", &curMat->Tr);
	}
	else if(memcmp(buffer, "Tf ", 3) == 0) {
		sscanf(buffer, "Tf %f %f %f", &curMat->Tf[0], &curMat->Tf[1], &curMat->Tf[2]);
	}
	else if(memcmp(buffer, "illum ", 6) == 0) {
		sscanf(buffer, "illum %d", &curMat->illum);
	}
	else if(memcmp(buffer, "Ka ", 3) == 0) {
		sscanf(buffer, "Ka %f %f %f", &curMat->Ka[0], &curMat->Ka[1], &curMat->Ka[2]);
	}
	else if(memcmp(buffer, "Kd ", 3) == 0) {
		sscanf(buffer, "Kd %f %f %f", &curMat->Kd[0], &curMat->Kd[1], &curMat->Kd[2]);
	}
	else if(memcmp(buffer, "Ks ", 3) == 0) {
		sscanf(buffer, "Ks %f %f %f", &curMat->Ks[0], &curMat->Ks[1], &curMat->Ks[2]);
	}
	
}