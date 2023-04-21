#include "../../include/engine/group.h"

Group::Group(){}

Group::Group(XMLElement *groupElement){
    color = NULL;
    label = NULL;

    if (groupElement->Attribute("label")) {
        label = strdup((char*)groupElement->Attribute("label"));
    }

    for(XMLElement *elem = groupElement->FirstChildElement(); elem; elem = elem->NextSiblingElement()){
        string name(elem->Name());

        if(name == "transform"){
            for(XMLElement *transformElem = elem->FirstChildElement(); transformElem; transformElem = transformElem->NextSiblingElement()){
                string transform(transformElem->Name());

                // Distinguir dinamico e estatico
                if(transform == "translate"){
                    transforms.push_back(new TranslateDynamic(transformElem));
                }
                else if(transform == "rotate"){
                    transforms.push_back(new RotateStatic(transformElem));
                }
                else if(transform == "scale"){
                    transforms.push_back(new Scale(transformElem));
                }
            }
        }
        else if(name == "models"){
            for(XMLElement *modelElem = elem->FirstChildElement(); modelElem; modelElem = modelElem->NextSiblingElement()){
                string name(modelElem->Name());

                if(name == "model"){
                    models.push_back(Model(modelElem));
                }                
            }
        }
        else if(name == "group"){
            groups.push_back(Group(elem));
        }
        else if (name == "color") {
            color = new Point(atof((char*)elem->Attribute("R")), atof((char*)elem->Attribute("G")), atof((char*)elem->Attribute("B")));
        }
    }
}


void Group::loadModels(){
    for(int i = 0; i < models.size(); i++){
        models[i].load();
    }

    for(int i = 0; i < groups.size(); i++){
        groups[i].loadModels();
    }
}


void Group::drawModels(){
    glPushMatrix();

    if (color != NULL) {
        glColor3f(color->x / 255.0, color->y / 255.0, color->z / 255.0);
    }

    for(int i = 0; i < transforms.size(); i++){
        transforms[i]->transform();
    }
    
    for(int i = 0; i < models.size(); i++){
        models[i].draw();
    }    

    for(int i = 0; i < groups.size(); i++){
        groups[i].drawModels();
    }

    glPopMatrix();
}


void Group::getLabels(vector<string>* labels) {
    labels->push_back(label); 

    for (int i = 0; i < groups.size(); i++) {
        groups[i].getLabels(labels);
    }
}