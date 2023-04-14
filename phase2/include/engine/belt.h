#ifndef __BELT__
#define __BELT__

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../point.h"
#include "../tinyxml2/tinyxml2.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif


using namespace tinyxml2;
using namespace std;

class Belt{
    public:
        char *path;
        int n;
        float radiusIn;
        float radiusOut;
        float verticalAngle;
        int seed;
        Point *color;

        int nVertices;
        int nIndexes;
        GLuint vertices_buffer;
        GLuint indexes_buffer;        

        Belt(XMLElement *elem);
        void load();
        void draw();
}

#endif