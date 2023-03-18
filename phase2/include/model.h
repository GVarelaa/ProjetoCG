#ifndef __MODEL__
#define __MODEL__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include 

using namespace std;

class Model{
    public:
        char *path;
        int nVertices;
        int nIndexes;
        GLuint vertices_buffer;
        GLuint indexes_buffer;

        Model();
        Model(XMLElement *elem);
        void load();
        void draw();
};

#endif
