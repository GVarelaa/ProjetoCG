#ifndef __CONE__
#define __CONE__

#include "point.h"
#include "triangle.h"
#include "model.h"
#include <vector>

using namespace std;

Model generate_cone(float radius, float height, int slices, int stacks);

#endif