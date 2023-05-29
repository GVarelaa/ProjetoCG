#include "../../include/engine/color.h"


Color::Color(XMLElement* elem) {
    XMLElement* child = elem->FirstChildElement();
    
    if (child != NULL){
        string name(child->Name());
        if (name == "diffuse"){
            diffuse[0] = atof((char*)child->Attribute("R"));
            diffuse[1] = atof((char*)child->Attribute("G"));
            diffuse[2] = atof((char*)child->Attribute("B"));
        }
        else if (name == "ambient"){
            ambient[0] = atof((char*)child->Attribute("R"));
            ambient[1] = atof((char*)child->Attribute("G"));
            ambient[2] = atof((char*)child->Attribute("B"));
        }
        else if (name == "specular"){
            specular[0] = atof((char*)child->Attribute("R"));
            specular[1] = atof((char*)child->Attribute("G"));
            specular[2] = atof((char*)child->Attribute("B"));
        }
        else if (name == "emissive"){
            emissive[0] = atof((char*)child->Attribute("R"));
            emissive[1] = atof((char*)child->Attribute("G"));
            emissive[2] = atof((char*)child->Attribute("B"));
        }
        else if (name == "shininess"){
            shininess = atof((char*)child->Attribute("value"));
        }
    }
}