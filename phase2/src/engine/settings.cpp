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
    radius = 5;
    alpha = 0;
    beta = 0;
    speed = 2;
    firstTime = true;
    //direction = Point(1,0,0);

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

void Camera::updateDirection(){
    // Vetor D
    direction.x = lookAt.x - position.x;
    direction.y = lookAt.y - position.y;
    direction.z = lookAt.z - position.z;
    
    // Normalizar o vetor
    direction.normalizeVector();
}


void Camera::updateLateralDirection(){
    // Vetor R
    direction.x = lookAt.x - position.x;
    direction.y = lookAt.y - position.y;
    direction.z = lookAt.z - position.z;
    
    // Produto externo
    direction.crossProduct(up);

    // Normalizar o vetor
    direction.normalizeVector();
}

void Camera::updatePosition(){
    position.x = radius * cos(beta) * sin(alpha);
    position.y = radius * sin(beta);
    position.z = radius * cos(beta) * cos(alpha);
}

void Camera::updateFPSPosition(int coef){
    position.x = position.x + coef * speed * direction.x;
    position.y = position.y + coef * speed * direction.y;
    position.z = position.z + coef * speed * direction.z;

    lookAt.x = lookAt.x + coef * speed * direction.x;
    lookAt.y = lookAt.y + coef * speed * direction.y;
    lookAt.z = lookAt.z + coef * speed * direction.z;
}

void Camera::processNormalKeys(unsigned char key){
    key = tolower(key);
    switch(key){
        case 'c':
            if(mode == STATIC)
                mode = EXPLORER;
            else if(mode == EXPLORER)
                mode = STATIC;
            break;
        case '-':
            if(mode == EXPLORER){
                radius += 5;
                updatePosition();
            }
            break;
        case '+':
            if(mode == EXPLORER){
                radius -= 5;
                updatePosition();
            }
            break;
        case 'w':
            if(mode == FPS){
                updateDirection();
                updateFPSPosition(1);
            }
            break;
        case 's':
            if(mode == FPS){
                updateDirection();
                updateFPSPosition(-1);
            }
            break;
        case 'a':
            if(mode == FPS){
                updateLateralDirection();
                updateFPSPosition(-1);
            }
            break;
        case 'd':
            if(mode == FPS){
                updateLateralDirection();
                updateFPSPosition(1);
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

void Camera::processMouseMotion(int x, int y){
    if(mode == FPS || mode == EXPLORER){
        if(firstTime){
            firstTime = false;
            startX = x;
            startY = y;
        }

        float deltaX = (x - startX) * 0.01;
        float deltaY = (y - startY) * 0.01;

        startX = x;
        startY = y;

        alpha += deltaX;

        if(beta + deltaY <= M_PI && beta + deltaY >= 0){
            beta += deltaY;
        }

        lookAt.x = position.x + sin(alpha) * sin(beta);
        lookAt.y = position.y + cos(beta);
        lookAt.z = position.z - cos(alpha) * sin(beta);
    }
}

// -----------PROJECTION-----------
Projection::Projection(){}

Projection::Projection(float newFov, float newNear, float newFar){
    fov = newFov;
    near = newNear;
    far = newFar;
}