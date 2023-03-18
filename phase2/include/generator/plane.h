#ifndef __PLANE__
#define __PLANE__

#include <vector>
#include "../point.h"
#include "../triangle.h"
#include "../model.h"

using namespace std;

pair<vector<Point>, vector<Triangle> > generatePlane(float length, int divisions);

#endif