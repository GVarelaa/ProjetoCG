#ifndef __MODEL__
#define __MODEL__

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

class Model{
    public:
        char* path;
        Point* color;
        int nIndexes;
        GLuint vertices_buffer;
        GLuint indexes_buffer;
        GLuint normals_buffer;
        GLuint tex_coords_buffer;


        Model();
        Model(XMLElement* elem);
        Model(char* path);
        void load();
        void draw();
};

#endif
