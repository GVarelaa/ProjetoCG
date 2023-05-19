#ifndef __PLANE__
#define __PLANE__

#include <vector>
#include "../point.h"
#include "../triangle.h"

using namespace std;

void generatePlane(float length, int divisions, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals, vector<Point> *texCoords);

#endif