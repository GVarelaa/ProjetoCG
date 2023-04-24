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

        virtual void transform(){};
};


class TranslateStatic : public Transformation{
    public:
        TranslateStatic(XMLElement *elem);
        void transform();
};


class TranslateDynamic : public Transformation{
    public:
        vector<Point> points;
        float time;
        bool align;
        int pointCount;
        Point yi; // Y Vector
        int tesselation;

        TranslateDynamic(XMLElement *elem);
        void transform();
        void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv);
        void getCatmullRomPoint(float t, int *indexes, float *pos, float *deriv);
        static void multMatrixVector(float *m, float *v, float *res);
        static void buildRotMatrix(Point x, Point y, Point z, float *m);
};


class RotateStatic : public Transformation{
    public:
        float angle;

        RotateStatic(XMLElement *elem);
        void transform();
};


class RotateDynamic : public Transformation{
    public:
        float time;

        RotateDynamic(XMLElement *elem);
        void transform();
};

class Scale : public Transformation{
    public:
        Scale(XMLElement *elem);
        void transform();
};

#endif

