#include "../../include/engine/transformation.h"

TranslateStatic::TranslateStatic(XMLElement *elem){
    x = atof((char *)elem->Attribute("x"));
    y = atof((char *)elem->Attribute("y"));
    z = atof((char *)elem->Attribute("z"));
}

void TranslateStatic::transform(){
    glTranslatef(x, y, z);
}

TranslateDynamic::TranslateDynamic(XMLElement *elem){
    curveTime = atof((char *)elem->Attribute("time"));
    
    if (!strcmp((char *)elem->Attribute("align"), "True")){
        align = true;
    } else if (!strcmp((char *)elem->Attribute("align"), False)){
        align = false;
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

void TranslateDynamic::transform(){

}


RotateStatic::RotateStatic(XMLElement *elem){
    x = atof((char *)elem->Attribute("x"));
    y = atof((char *)elem->Attribute("y"));
    z = atof((char *)elem->Attribute("z"));
    angle = atof((char *)elem->Attribute("angle"));
}

void RotateStatic::transform(){
    glRotatef(angle, x, y, z);
}

RotateDynamic::RotateDynamic(XMLElement *elem){
    x = atof((char *)elem->Attribute("x"));
    y = atof((char *)elem->Attribute("y"));
    z = atof((char *)elem->Attribute("z"));
    time = atof((char *)elem->Attribute("time"));
}

void RotateDynamic::transform(){
    
}


Scale::Scale(XMLElement *elem){
    x = atof((char *)elem->Attribute("x"));
    y = atof((char *)elem->Attribute("y"));
    z = atof((char *)elem->Attribute("z"));
}

void Scale::transform(){
    glScalef(x, y, z);
}