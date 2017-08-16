#include "objloader.h"
#include <fstream>
#include <iostream>
#include <string.h>

bool updatebyline(ObjModel* model, string line);

vector<ObjModel*>* loadModel(char const * filename)
{
  ifstream f(filename);
  vector<ObjModel*>* models = new vector<ObjModel*>();
  if(f.is_open()) {
    string line;
    ObjModel* model = new ObjModel();
    while(getline(f, line)) {
      if(updatebyline(model, line)) {
	models->push_back(model);
	model = new ObjModel();
      }
    }
    f.close();
  }
  return models;
}

bool updatebyline(ObjModel* model, string line) {
  const char* data = line.c_str();
  Vector3 *vec;
  if(memcmp(data, "v ", 2) == 0) {
    //vertex
    vec = new Vector3();
    sscanf(data, "v %f %f %f", &vec->x, &vec->y, &vec->z);
    model->getVertex()->push_back(vec);
    return false;
  }
  else if(memcmp(data, "vn ", 3) == 0) {
    //normal
    vec = new Vector3();
    sscanf(data, "vn %f %f %f", &vec->x, &vec->y, &vec->z);
    model->getNormal()->push_back(vec);
    return false;
  }
  else if(memcmp(data, "vt ", 3) == 0) {
    //texture
    vec = new Vector3();
    sscanf(data, "vt %f %f %f", &vec->x, &vec->y, &vec->z);
    model->getTex()->push_back(vec);
    return false;
  }
  else if(memcmp(data, "f ", 2) == 0) {
    //face
    //face는 어떻게 처리?
    return false;
  }
  else if(memcmp(data, "g ", 2) == 0) {
    return true;
  }
  return false;
}
