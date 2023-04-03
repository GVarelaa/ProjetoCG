#ifndef __POINT__
#define __POINT__

#include <math.h>

class Point { 
    public:
        float x;  
        float y;  
        float z;
        Point();
        Point(float x1, float y1, float z1);
        void normalizeVector();
        void crossProduct(Point v);
};

#endif