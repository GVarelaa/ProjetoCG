#ifndef __TRANSFORM__
#define __TRANSFORM__


#include "../tinyxml2/tinyxml2.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

using namespace tinyxml2;

class Transform{
    public:
        float x;
        float y;
        float z;

        virtual void transform(){};
};

class Translate : public Transform{
    public:
        Translate(float x, float y, float z);
        Translate(XMLElement *elem);
        void transform();
};

class Rotate : public Transform{
    public:
        float angle;

        Rotate(float x, float y, float z, float angle);
        Rotate(XMLElement *elem);
        void transform();
};

class Scale : public Transform{
    public:
        Scale(float x, float y, float z);
        Scale(XMLElement *elem);
        void transform();
};

#endif

