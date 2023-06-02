#include "../../include/engine/world.h"

World::World(){}

World::World(Window newWindow, Camera newCamera, vector<Group> newGroups){
    window = newWindow;
    camera = newCamera;
    groups = newGroups;
}


World::World(char *path){
    XMLDocument xmlDoc;
	XMLError result = xmlDoc.LoadFile(path);
	XMLElement *root = xmlDoc.FirstChildElement("world");
    
    for(XMLElement *elem = root->FirstChildElement(); elem; elem=elem->NextSiblingElement()){
        string name(elem->Name());

        if(name == "window"){
            window = Window(elem);
        }
        else if(name == "camera"){
            camera = Camera(elem);
        }
        else if(name == "group"){
            groups.push_back(Group(elem));
        }
        else if (name == "lights"){
            for(XMLElement *child = elem->FirstChildElement(); child; child=child->NextSiblingElement()){
                string childName(child->Name());

                if (childName == "light"){
                    if (!strcmp((char *)child->Attribute("type"), "point")){
                        lights.push_back(new PointLight(child));
                    }
                    else if (!strcmp((char *)child->Attribute("type"), "directional")){
                        lights.push_back(new DirectionalLight(child));
                    }
                    else if (!strcmp((char *)child->Attribute("type"), "spotlight")){
                        lights.push_back(new SpotLight(child));               
                    }
                }
            }
        }
    }
}


void World::loadModels(){
    for(int i = 0; i < groups.size(); i++){
        groups[i].loadModels();
    }
}


void World::drawModels(){
    for(int i = 0; i < groups.size(); i++){
        groups[i].drawModels();
    }
}


vector<char *> World::getLabels() {
    vector<char *> labels;

    for (int i = 0; i < groups.size(); i++) {
        groups[i].getLabels(&labels);
    }

    return labels;
}


Point* World::getGroupPosition(int n){
    for(int i=0; i<groups.size(); i++){
        float matrix[4][4] = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        };
        Point *p = groups[i].getGroupPosition(matrix, &n);

        if(p) return new Point(p->x, p->y, p->z);
    }

    return NULL;
}


int World::getClosestGroupIndex(){
    int n=0;
    for(int i=0; i<groups.size(); i++){
        groups[i].getGroupsNumber(&n);
    }
    
    vector<pair<Point*, int> > labeledGroups;
    for(int i=0; i<n; i++){
        Point *p = getGroupPosition(i);
        if(p){
            labeledGroups.push_back(pair<Point*, int>(p, i));
        }
    }
    
    if(labeledGroups.size() > 0){
        int n = 0;
        for(int i=0; i<labeledGroups.size(); i++){
            if(labeledGroups[i].first->distanceTo(camera.position) < labeledGroups[n].first->distanceTo(camera.position)){
                n = i;
            }
        }

        return labeledGroups[n].second;
    }
    else return 0;
}


void World::applyLights(){
    for(int i=0; i<lights.size(); i++){
        lights[i]->apply(i);
    }
}