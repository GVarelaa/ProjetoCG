#ifndef __SETTINGS__
#define __SETTINGS__

#include "point.h"
#include "tinyxml2/tinyxml2.h"

class Window{
    public:
        int width;
        int height;
        Window();
        Window(int newHeight, int newWidth);
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

class Camera{
    public:
        Point position;
        Point lookAt;
        Point up; 
        Projection projection;
        Camera();
        Camera(Point newPosition, Point newLookAt, Point newUp, Projection newProjection);
        Camera(XMLElement *cameraElement);
};

#endif