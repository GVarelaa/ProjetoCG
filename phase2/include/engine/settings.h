#ifndef __SETTINGS__
#define __SETTINGS__

#include "../point.h"
#include "../tinyxml2/tinyxml2.h"
#include <string>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

using namespace std;
using namespace tinyxml2;

class Window{
    public:
        int width;
        int height;

        Window();
        Window(XMLElement *windowElement);
};

class Projection{
    public:
        float fov;
        float near;
        float far;

        Projection();
        Projection(float newFov, float newNear, float newFar);
};

enum Mode{STATIC, EXPLORER, FPS};

class Camera{
    public:
        Point position;
        Point direction;
        Point lookAt;
        Point up; 
        Projection projection;
        Mode mode;

        float radius;
        float alpha;
        float beta;

        Camera();
        Camera(XMLElement *cameraElement);
        void processNormalKeys(unsigned char key);
        void processSpecialKeys(int key);
        void updatePosition();
        void updateFPSPosition();
};

#endif