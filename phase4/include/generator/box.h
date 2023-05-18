#ifndef __BOX__
#define __BOX__

#include <vector>
#include "../point.h"
#include "../triangle.h"

using namespace std;

void generateBox(float length, int divisions, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals);

#endif