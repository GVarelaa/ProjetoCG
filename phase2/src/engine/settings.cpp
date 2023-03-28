#include "../../include/engine/settings.h"

// -----------WINDOW-----------
Window::Window(){}

Window::Window(XMLElement *windowElement){
    width = atoi(windowElement->Attribute("width"));
    height = atoi(windowElement->Attribute("height"));
}


// -----------CAMERA-----------
Camera::Camera(){}

Camera::Camera(XMLElement *cameraElement){
    up = Point(0, 1, 0); // Default value
    projection = Projection(60, 1, 1000); // Default value
    mode = STATIC;
    radius = 10;
    alpha = 0;
    beta = 0;
    direction = Point(1,0,0);

    if(cameraElement->Attribute("mode")){
        string name(cameraElement->Attribute("mode"));

        if(name == "static"){
            mode = STATIC;
        }
        else if(name == "explorer"){
            mode = EXPLORER;
        }
        else if(name == "fps"){
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

void Camera::updatePosition(){
    position.x = radius * cos(beta) * sin(alpha);
    position.y = radius * sin(beta);
    position.z = radius * cos(beta) * cos(alpha);
}

void Camera::updateFPSPosition(){
    position.x = position.x + direction.x * 1;
    position.y = position.y + direction.y * 1;
    position.z = position.z + direction.z * 1;
}

void Camera::processNormalKeys(unsigned char key){
    switch(key){
        case 'c':
            if(mode == STATIC)
                mode = EXPLORER;
            else if(mode == EXPLORER)
                mode = STATIC;
            break;
        case '-':
            if(mode == EXPLORER){
                radius += 1;
                updatePosition();
            }
            break;
        case '+':
            if(mode == EXPLORER){
                radius -= 1;
                updatePosition();
            }
            break;
        case 'w':
            if(mode == FPS){
                printf("aqui\n");
                updateFPSPosition();
            }
            break;
    }
}

void Camera::processSpecialKeys(int key){
    switch(key){
        case GLUT_KEY_LEFT:
            if(mode == EXPLORER){
                alpha -= M_PI / 20;
                updatePosition();
            }
            break;
        case GLUT_KEY_RIGHT:
            if(mode == EXPLORER){
                alpha += M_PI / 20;
                updatePosition();
            }
            break;
        case GLUT_KEY_UP:
            if(mode == EXPLORER){
                beta += M_PI / 20;

			    if (beta > M_PI / 2) beta = M_PI / 2;
                updatePosition();
            }
            break;
        case GLUT_KEY_DOWN:
            if(mode == EXPLORER){
                beta -= M_PI / 20;

			    if (beta < -M_PI / 2) beta = -M_PI / 2;
                updatePosition();
            }
            break;
    }
}

// -----------PROJECTION-----------
Projection::Projection(){}

Projection::Projection(float newFov, float newNear, float newFar){
    fov = newFov;
    near = newNear;
    far = newFar;
}