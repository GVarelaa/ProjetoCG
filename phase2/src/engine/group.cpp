#include "../../include/engine/group.h"

Group::Group(){}

Group::Group(XMLElement *groupElement){
    for(XMLElement *elem = groupElement->FirstChildElement(); elem; elem = elem->NextSiblingElement()){
        string name(elem->Name());

        if(name == "transform"){
            for(XMLElement *transformElem = elem; transformElem; transformElem = transformElem->NextSiblingElement()){
                string transform(transformElem->Name());

                if(transform == "translate"){
                    transforms.push_back(Translate(transformElem));
                }
                else if(transform == "rotate"){
                    transforms.push_back(Rotate(transformElem));
                }
                else if(transform == "scale"){
                    transforms.push_back(Scale(transformElem));
                }
            }
        }
        else if(name == "model"){
            for(XMLElement *modelElem = elem; modelElem; modelElem = modelElem->NextSiblingElement()){
                models.push_back(Model(modelElem));
            }
        }
        else if(name == "group"){
            groups.push_back(Group(elem));
        }
    }
}

Group::Group(vector<Model> newModels){
    models = newModels;
}

