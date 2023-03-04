#include "../include/world.h"

Window::Window(){
    
}

Window::Window(int new_width, int new_height){
    width = new_width;
    height = new_height;
}

World::World(char *path){
    XMLDocument xml_doc;
	XMLError result = xml_doc.LoadFile(path);
	XMLNode *root = xml_doc.FirstChild();
	if(root){
        XMLElement *window_element = root->FirstChildElement("window");
        if(window_element){
            int width = atoi(window_element->Attribute("width"));
            int height = atoi(window_element->Attribute("height"));
            window = Window(width, height);
        }

        XMLElement *camera_element = root->FirstChildElement("camera");
        if(camera_element){
            XMLElement *position_element = camera_element->FirstChildElement("position");
            float position_x = atof(position_element->Attribute("x"));
            float position_y = atof(position_element->Attribute("y"));
            float position_z = atof(position_element->Attribute("z"));
            

            XMLElement *lookAt_element = camera_element->FirstChildElement("lookAt");
            float lookAt_x = atof(lookAt_element->Attribute("x"));
            float lookAt_y = atof(lookAt_element->Attribute("y"));
            float lookAt_z = atof(lookAt_element->Attribute("z"));
        
            XMLElement *up_element = camera_element->FirstChildElement("up");
            float up_x = atof(up_element->Attribute("x"));
            float up_y = atof(up_element->Attribute("y"));
            float up_z = atof(up_element->Attribute("z"));

            XMLElement *projection_element = camera_element->FirstChildElement("projection");
            float projection_fov = atof(projection_element->Attribute("fov"));
            float projection_near = atof(projection_element->Attribute("near"));
            float projection_far = atof(projection_element->Attribute("far"));

            camera = Camera(Point(position_x, position_y, position_z), Point(lookAt_x, lookAt_y, lookAt_z), Point(up_x, up_y, up_z), Projection(projection_fov, projection_near, projection_far));
        }

        XMLElement *group_element = root->FirstChildElement("group");
        if(group_element){
            XMLElement *models_element = group_element->FirstChildElement("models");
            if(models_element){
                vector<Model> models;
                for (XMLElement *model_element = models_element->FirstChildElement("model"); model_element; model_element = model_element->NextSiblingElement("model")){
                   char *path = (char *)model_element->Attribute("file");
                   models.push_back(Model(path));
                }
                group = Group(models);
            }
        }     
	}
}

int Window::get_width(){
    return width;
}


int Window::get_height(){
    return height;
}

Projection::Projection(){

}

Projection::Projection(float new_fov, float new_near, float new_far){
    fov = new_fov;
    near = new_near;
    far = new_far;
}


float Projection::get_fov(){
    return fov;
}

float Projection::get_near(){
    return near;
}

float Projection::get_far(){
    return far;
}

Camera::Camera(){

}

Camera::Camera(Point new_position, Point new_lookAt, Point new_up, Projection new_projection){
    position = new_position;
    lookAt = new_lookAt;
    up = new_up;
    projection = new_projection;
}

Point Camera::get_position(){
    return position;
}

Point Camera::get_lookAt(){
    return lookAt;
}

Point Camera::get_up(){
    return up;
}

Projection Camera::get_projection(){
    return projection;
}

Group::Group(){
}

Group::Group(vector<Model> new_models){
    models = new_models;
}

World::World(Window new_window, Camera new_camera, Group new_group){
    window = new_window;
    camera = new_camera;
    group = new_group;
}

Window World::get_window(){
    return window;
}

Camera World::get_camera(){
    return camera;
}

Group World::get_group(){
    return group;
}