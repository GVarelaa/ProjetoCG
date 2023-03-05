#ifndef __SPHERE__
#define __SPHERE__

#include "point.h"
#include "triangle.h"
#include "model.h"
#include <vector>

using namespace std;

Model generateSphere(float radius, int slices, int stacks);

#endif