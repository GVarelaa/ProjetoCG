#ifndef __TRANSFORMATION__
#define __TRANSFORMATION__

#include <vector>
#include <iostream>
#include "../tinyxml2/tinyxml2.h"
#include "../point.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

using namespace std;
using namespace tinyxml2;

class Transformation{
    public:
        float x;
        float y;
        float z;
        vector<Point> curvePoints;
        float curveTime;
        bool align;

        virtual void transform(){};
};

class Translate : public Transformation{
    public:
        Translate(float x, float y, float z);
        Translate(XMLElement *elem);
        void transform();
};

class Rotate : public Transformation{
    public:
        float angle;

        Rotate(float x, float y, float z, float angle);
        Rotate(XMLElement *elem);
        void transform();
};

class Scale : public Transformation{
    public:
        Scale(float x, float y, float z);
        Scale(XMLElement *elem);
        void transform();
};

#endif

