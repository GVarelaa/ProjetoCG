#include "../../include/engine/world.h"

World::World(){}

World::World(Window newWindow, Camera newCamera, Group newGroup){
    window = newWindow;
    camera = newCamera;
    group = newGroup;
}

World::World(char *path){
    XMLDocument xmlDoc;
	XMLError result = xmlDoc.LoadFile(path);
	XMLNode *root = xmlDoc.FirstChild();
    
	if(root){
        XMLElement *windowElement = root->FirstChildElement("window");
        if(windowElement){
            window = Window(windowElement);
        }

        XMLElement *cameraElement = root->FirstChildElement("camera");
        if(cameraElement){
            camera = Camera(cameraElement);
        }
    
        XMLElement *groupElement = root->FirstChildElement("group");
        if(groupElement){
            XMLElement *modelsElement = groupElement->FirstChildElement("models");
            if(modelsElement){
                vector<string> modelsPaths;
                for (XMLElement *modelElement = modelsElement->FirstChildElement("model"); modelElement; modelElement = modelElement->NextSiblingElement("model")){               
                    const char *path = (char *)modelElement->Attribute("file");
                    modelsPaths.push_back(string(path));
                }
                group = Group(modelsPaths);
            }
        }
	}
}

void World::loadGroup(){
    for(int i = 0; i<group.modelsPaths.size(); i++){
        group.vbos.push_back(VBO((char *)group.modelsPaths[i].c_str()));
    }
}
