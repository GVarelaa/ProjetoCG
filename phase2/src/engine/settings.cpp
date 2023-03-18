#include "../../include/engine/settings.h"

// -----------WINDOW-----------
Window::Window(){}

Window::Window(int newWidth, int newHeight){
    width = newWidth;
    height = newHeight;
}

Window::Window(XMLElement *windowElement){
    width = atoi(windowElement->Attribute("width"));
    height = atoi(windowElement->Attribute("height"));
}


// -----------CAMERA-----------
Camera::Camera(){}

Camera::Camera(Point newPosition, Point newLookAt, Point newUp, Projection newProjection){
    position = newPosition;
    lookAt = newLookAt;
    up = newUp;
    projection = newProjection;
}

Camera::Camera(XMLElement *cameraElement){
    XMLElement *positionElement = cameraElement->FirstChildElement("position");
    float positionX = atof(positionElement->Attribute("x"));
    float positionY = atof(positionElement->Attribute("y"));
    float positionZ = atof(positionElement->Attribute("z"));
    

    XMLElement *lookAtElement = cameraElement->FirstChildElement("lookAt");
    float lookAtX = atof(lookAtElement->Attribute("x"));
    float lookAtY = atof(lookAtElement->Attribute("y"));
    float lookAtZ = atof(lookAtElement->Attribute("z"));

    XMLElement *upElement = cameraElement->FirstChildElement("up");
    float upX = atof(upElement->Attribute("x"));
    float upY = atof(upElement->Attribute("y"));
    float upZ = atof(upElement->Attribute("z"));

    XMLElement *projectionElement = cameraElement->FirstChildElement("projection");
    float projectionFov = atof(projectionElement->Attribute("fov"));
    float projectionNear = atof(projectionElement->Attribute("near"));
    float projectionFar = atof(projectionElement->Attribute("far"));

    position = Point(positionX, positionY, positionZ);
    lookAt = Point(lookAtX, lookAtY, lookAtZ);
    up = Point(upX, upY, upZ);
    projection = Projection(projectionFov, projectionNear, projectionFar);
}


// -----------PROJECTION-----------
Projection::Projection(){}

Projection::Projection(float newFov, float newNear, float newFar){
    fov = newFov;
    near = newNear;
    far = newFar;
}