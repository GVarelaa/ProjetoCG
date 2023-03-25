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
    up = Point(0, 1, 0); // Default value
    projection = Projection(60, 1, 1000); // Default value
    mode = STATIC;

    if(cameraElement->Attribute("mode")){
        string name(cameraElement->Attribute("mode"));

        if(name == "static"){
            mode = STATIC;
        }
        else if(name == "explorer"){
            mode = EXPLORER;
        }
        else if(name == "FPS"){
            mode = FPS;
        }
    }

    for(XMLElement *elem = cameraElement->FirstChildElement(); elem; elem=elem->NextSiblingElement()){
        string name(elem->Name());
        
        if(name == "position"){
            position = Point(atof(elem->Attribute("x")), atof(elem->Attribute("y")), atof(elem->Attribute("z")));
        }
        else if(name == "lookAt"){
            lookAt = Point(atof(elem->Attribute("x")), atof(elem->Attribute("y")), atof(elem->Attribute("z")));
        }
        else if(name == "up"){
            up = Point(atof(elem->Attribute("x")), atof(elem->Attribute("y")), atof(elem->Attribute("z")));
        }
        else if(name == "projection"){
            projection = Projection(atof(elem->Attribute("fov")), atof(elem->Attribute("near")), atof(elem->Attribute("far")));
        }
    }
}


// -----------PROJECTION-----------
Projection::Projection(){}

Projection::Projection(float newFov, float newNear, float newFar){
    fov = newFov;
    near = newNear;
    far = newFar;
}