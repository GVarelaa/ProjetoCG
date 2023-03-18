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
#include "../tinyxml2/tinyxml2.h"

using namespace tinyxml2;
using namespace std;

class Model{
    public:
        int nVertices;
        int nIndexes;
        GLuint vertices_buffer;
        GLuint indexes_buffer;
        char *path;

        Model(char* path);
        Model(XMLElement *elem);
	Model();
        void draw();
};

#endif
