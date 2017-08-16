#include <fstream>
#include <iostream>
#include "objloader.h"

using namespace std;

int testLoadModel1(void) {
  vector<ObjModel*>* models = loadModel("POLICE BIKE.obj");
  vector<Vector3*>* vec = models[0][0]->getVertex();
  
  cout << "start" << endl;
  cout << vec->size() << endl;
  
  cout << "middle" << endl;
  for(vector<Vector3*>::iterator i = vec->begin(); i != vec->end(); i++) {
    cout << (*i)->x << "," << (*i)->y << "," << (*i)->z << endl;
  }
  
  return 0;
}

int main(void) {
}