#include <vector>
#include <string>

using namespace std;

typedef struct Vector3 {
  float x, y, z;
} Vector3;


class ObjModel {
private:
  vector<Vector3*> vertex, tex, normal;
public:
  void draw();
  vector<Vector3*>* getVertex() { return &vertex; }
  vector<Vector3*>* getTex() { return &tex; }
  vector<Vector3*>* getNormal() { return &normal; }
};

vector<ObjModel*>* loadModel(char const * filename); 