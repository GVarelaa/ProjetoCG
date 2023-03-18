#ifndef __TORUS__
#define __TORUS__

#include <vector>
#include <math.h>
#include "../point.h"
#include "../triangle.h"
#include "../model.h"

using namespace std;

Model generateTorus(float radiusIn, float radiusOut, int slices, int layers);

#endif
