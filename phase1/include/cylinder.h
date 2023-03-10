#ifndef __CYLINDER__
#define __CYLINDER__

#include <math.h>
#include <vector>
#include "point.h"
#include "triangle.h"
#include "model.h"

using namespace std;

Model generateCylinder(float radius, float height, int slices);

#endif