#include "../../include/engine/transform.h"

Translate::Translate(float newX, float newY, float newZ){
    x = newX;
    y = newY;
    z = newZ;
}

Translate::Translate(XMLElement *elem){
    
}


Rotate::Rotate(float newX, float newY, float newZ, float newAngle){
    x = newX;
    y = newY;
    z = newZ;
    angle = newAngle;    
}


Scale::Scale(float newX, float newY, float newZ){
    x = newX;
    y = newY;
    z = newZ;
}

