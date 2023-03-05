#include "../include/world.h"

Window::Window(){
    
}

Window::Window(int newWidth, int newHeight){
    width = newWidth;
    height = newHeight;
}

Projection::Projection(){}

Projection::Projection(float newFov, float newNear, float newFar){
    fov = newFov;
    near = newNear;
    far = newFar;
}

Camera::Camera(){}

Camera::Camera(Point newPosition, Point newLookAt, Point newUp, Projection newProjection){
    position = newPosition;
    lookAt = newLookAt;
    up = newUp;
    projection = newProjection;
}

Group::Group(){}

Group::Group(vector<Model> newModels){
    models = newModels;
}

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
            int width = atoi(windowElement->Attribute("width"));
            int height = atoi(windowElement->Attribute("height"));
            window = Window(width, height);
        }

        XMLElement *cameraElement = root->FirstChildElement("camera");
        if(cameraElement){
            XMLElement *positionElement = cameraElement->FirstChildElement("position");
            float positionX = atof(positionElement->Attribute("x"));
            float positionY = atof(positionElement->Attribute("y"));
            float positionZ = atof(positionElement->Attribute("z"));
            

            XMLElement *lookAtElement = cameraElement->FirstChildElement("lookAt");
            float lookAtX = atof(lookAtElement->Attribute("x"));
            float lookAtY = atof(lookAtElement->Attribute("y"));
            float lookAtZ = atof(lookAtElement->Attribute("z"));
        
            XMLElement *upElement = cameraElement->FirstChildElement("up");
            float upX = atof(upElement->Attribute("x"));
            float upY = atof(upElement->Attribute("y"));
            float upZ = atof(upElement->Attribute("z"));

            XMLElement *projectionElement = cameraElement->FirstChildElement("projection");
            float projectionFov = atof(projectionElement->Attribute("fov"));
            float projectionNear = atof(projectionElement->Attribute("near"));
            float projectionFar = atof(projectionElement->Attribute("far"));

            camera = Camera(Point(positionX, positionY, positionZ), Point(lookAtX, lookAtY, lookAtZ), Point(upX, upY, upZ), Projection(projectionFov, projectionNear, projectionFar));
        }
        
        XMLElement *groupElement = root->FirstChildElement("group");

        if(groupElement){
            XMLElement *modelsElement = groupElement->FirstChildElement("models");
            if(modelsElement){
                vector<Model> models;
                for (XMLElement *modelElement = modelsElement->FirstChildElement("model"); modelElement; modelElement = modelElement->NextSiblingElement("model")){
                   char *path = (char *)modelElement->Attribute("file");
                   models.push_back(Model(path));
                }
                group = Group(models);
            }
        } 
	}
}