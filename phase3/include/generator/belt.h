#ifndef __BELT__
#define __BELT__

#include <vector>
#include <stdlib.h>
#include "../point.h"
#include "../triangle.h"
#include "../generator/ellipsoid.h"

using namespace std;

pair<vector<Point>, vector<Triangle> > generateBelt(int n, float radiusIn, float radiusOut, float height, float lengthMin, float lengthMax, int seed);

#endif