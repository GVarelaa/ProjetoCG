#include "../../include/engine/transform.h"

Translate::Translate(float newX, float newY, float newZ){
    x = newX;
    y = newY;
    z = newZ;
}

Translate::Translate(XMLElement *elem){
    x = atof((char *)elem->Attribute("x"));
    y = atof((char *)elem->Attribute("y"));
    z = atof((char *)elem->Attribute("z"));
}


Rotate::Rotate(float newX, float newY, float newZ, float newAngle){
    x = newX;
    y = newY;
    z = newZ;
    angle = newAngle;    
}

Rotate::Rotate(XMLElement *elem){
    x = atof((char *)elem->Attribute("x"));
    y = atof((char *)elem->Attribute("y"));
    z = atof((char *)elem->Attribute("z"));
    angle = atof((char *)elem->Attribute("angle"));
}


Scale::Scale(float newX, float newY, float newZ){
    x = newX;
    y = newY;
    z = newZ;
}

Scale::Scale(XMLElement *elem){
    x = atof((char *)elem->Attribute("x"));
    y = atof((char *)elem->Attribute("y"));
    z = atof((char *)elem->Attribute("z"));
}
