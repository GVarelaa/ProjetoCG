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

                if (childName == "lights"){
                    if ((char *)child->Attribute("type") == "point"){
                        float posX = atof((char *)child->Attribute("posX"));
                        float posY = atof((char *)child->Attribute("posY"));
                        float posZ = atof((char *)child->Attribute("posZ"));

                        float pos[4] = {posX, posY, posZ, 1.0};
                        float quad_att = 1.0f;

                        glLightfv(GL_LIGHT0, GL_POSITION, pos);
                        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, quad_att);
                    }
                    else if ((char *)child->Attribute("type") == "directional"){
                        float dirX = atof((char *)child->Attribute("dirX"));
                        float dirY = atof((char *)child->Attribute("dirY"));
                        float dirZ = atof((char *)child->Attribute("dirZ"));

                        float dir[4] = {dirX, dirY, dirZ, 1.0};
                        glLightfv(GL_LIGHT0, GL_POSITION, dir);
                    }
                    else if ((char *)child->Attribute("type") == "spotlight"){
                        float posX = atof((char *)child->Attribute("posX"));
                        float posY = atof((char *)child->Attribute("posY"));
                        float posZ = atof((char *)child->Attribute("posZ"));
                        float dirX = atof((char *)child->Attribute("dirX"));
                        float dirY = atof((char *)child->Attribute("dirY"));
                        float dirZ = atof((char *)child->Attribute("dirZ"));

                        GLfloat pos[4] = {posX, posY, posZ, 1.0};
                        GLfloat spotDir[3] = {dirX, dirY, dirZ};

                        glLightfv(GL_LIGHT0, GL_POSITION, pos);
                        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
                        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, atof((char *)child->Attribute("cutoff")));
                        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0);                    
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