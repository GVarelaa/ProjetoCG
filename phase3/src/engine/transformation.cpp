#include "../../include/engine/transformation.h"

Translate::Translate(XMLElement *elem){
    x = atof((char *)elem->Attribute("x"));
    y = atof((char *)elem->Attribute("y"));
    z = atof((char *)elem->Attribute("z"));

    curveTime = 0;
    if (elem->Attribute("time")){
        curveTime = atof((char *)elem->Attribute("time"));
    }
    
    align = false;
    if (elem->Attribute("align") && !strcmp((char *)elem->Attribute("align"), "True")){
        align = true;
    }

    int i=0;
    for(XMLElement *childElem = elem->FirstChildElement(); childElem; childElem = childElem->NextSiblingElement(), i++){
        curvePoints.push_back(Point(childElem));
    }
    if (i < 4){
        cout << "ERROR: Due to Catmull-Rom's curve definition it is always required an initial point before the initial curve segment and another point after the last segment. The minimum number of points is 4" << endl;
        exit(1);
    }
}

void Translate::transform(){
    glTranslatef(x, y, z);
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

void Rotate::transform(){
    glRotatef(angle, x, y, z);
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

void Scale::transform(){
    glScalef(x, y, z);
}