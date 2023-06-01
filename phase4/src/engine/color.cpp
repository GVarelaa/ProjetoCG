#include "../../include/engine/color.h"


Color::Color(){}


Color::Color(XMLElement* elem) {
    for(XMLElement *child = elem->FirstChildElement(); child; child=child->NextSiblingElement()){
        string childName(child->Name());

        if (childName == "diffuse"){
            diffuse[0] = atof((char*)child->Attribute("R"));
            diffuse[1] = atof((char*)child->Attribute("G"));
            diffuse[2] = atof((char*)child->Attribute("B"));
        }
        else if (childName == "ambient"){
            ambient[0] = atof((char*)child->Attribute("R"));
            ambient[1] = atof((char*)child->Attribute("G"));
            ambient[2] = atof((char*)child->Attribute("B"));
        }
        else if (childName == "specular"){
            specular[0] = atof((char*)child->Attribute("R"));
            specular[1] = atof((char*)child->Attribute("G"));
            specular[2] = atof((char*)child->Attribute("B"));
        }
        else if (childName == "emissive"){
            emissive[0] = atof((char*)child->Attribute("R"));
            emissive[1] = atof((char*)child->Attribute("G"));
            emissive[2] = atof((char*)child->Attribute("B"));
        }
        else if (childName == "shininess"){
            shininess = atof((char*)child->Attribute("value"));
        }
    }
}