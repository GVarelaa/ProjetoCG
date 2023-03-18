#include "../../include/engine/group.h"

Group::Group(){}

Group::Group(XMLElement *groupElement){
    for(XMLElement *elem = groupElement->FirstChildElement(); elem; elem = elem->NextSiblingElement()){
        if(!strcmp(elem->Name(), "transform")){
            for(XMLElement *transformElem = elem; transformElem; transformElem = transformElem->NextSiblingElement()){
                if(!strcmp(transformElem->Name(), "translate")){
                    transforms.push_back(Transform(transformElem));
                }
            }
        }
        else if(!strcmp(elem->Name(), "models")){
            for(XMLElement *modelELem = elem; modelELem; modelELem = modelELem->NextSiblingElement()){
                models.push_back(Model(modelElem));
            }
        }
        else if(!strcmp(elem->Name(), "group")){
            groups.push_back(Group(elem));
        }
    }
}

Group::Group(vector<Model> newModels){
    models = newModels;
}

Group::Group(vector<string> newModelsPaths){
    modelsPaths = newModelsPaths;
}