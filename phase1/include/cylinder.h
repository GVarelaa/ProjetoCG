#ifndef __CYLINDER__
#define __CYLINDER__

#include "point.h"
#include "triangle.h"
#include "model.h"
#include <math.h>
#include <vector>

using namespace std;

Model generateCylinder(float radius, float height, int slices);

#endif