#include "../include/world.h"

Window::Window(){
    
}

Window::Window(int new_width, int new_height){
    width = new_width;
    height = new_height;
};

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