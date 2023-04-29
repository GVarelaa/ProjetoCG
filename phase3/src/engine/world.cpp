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


void World::calculatePositions(){
    for(int i=0; i<groups.size(); i++){
        float matrix[4][4] = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        };
        groups[i].calculatePositions(matrix);
    }
}


Point World::getGroupPosition(int n){
    for(int i=0; i<groups.size(); i++){
        Point *p = groups[i].getGroupPosition(&n);

        if(p) return Point(p->x, p->y, p->z);
    }

    return Point(0, 0, 0);
}



Point World::getClosestGroupPosition(){
    vector<Point> points;
    for(int i=0; i<groups.size(); i++){
        groups[i].getGroupPositions(&points);
    }
    
    if(points.size() > 0){
        Point p = points[0];
        for(int i=0; i<points.size(); i++){
            if(points[i].distanceTo(camera.position) < p.distanceTo(camera.position)){
                p = points[i];
            }
        }

        return p;
    }
    else return Point(0, 0, 0);
}