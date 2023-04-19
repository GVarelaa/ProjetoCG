#ifndef __BELT__
#define __BELT__

#include <vector>
#include <stdlib.h>
#include "../point.h"
#include "../triangle.h"

using namespace std;

pair<vector<Point>, vector<Triangle> > generateBelt(int n, float radiusIn, float radiusOut, float height, int seed);

#endif