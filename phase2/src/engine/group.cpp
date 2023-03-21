#include "../../include/engine/group.h"

Group::Group(){}

Group::Group(XMLElement *groupElement){
    for(XMLElement *elem = groupElement->FirstChildElement(); elem; elem = elem->NextSiblingElement()){
        string name(elem->Name());

        if(name == "transform"){
            for(XMLElement *transformElem = elem->FirstChildElement(); transformElem; transformElem = transformElem->NextSiblingElement()){
                string transform(transformElem->Name());

                if(transform == "translate"){
                    transforms.push_back(new Translate(transformElem));
                }
                else if(transform == "rotate"){
                    transforms.push_back(new Rotate(transformElem));
                }
                else if(transform == "scale"){
                    transforms.push_back(new Scale(transformElem));
                }
            }
        }
        else if(name == "models"){
            for(XMLElement *modelElem = elem->FirstChildElement(); modelElem; modelElem = modelElem->NextSiblingElement()){
                models.push_back(Model(modelElem));
            }
        }
        else if(name == "group"){
            groups.push_back(Group(elem));
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
