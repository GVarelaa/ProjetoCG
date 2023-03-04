#ifndef __WORLD__
#define __WORLD__

#include <vector>
#include "point.h"
#include "model.h"

using namespace std;

class Window{
    private:
    int width;
    int height;

    public:
    Window(int new_height, int new_width);
    int get_width();
    int get_height();
};

class Projection{
    private:
    float fov;
    float near;
    float far;

    public:
    Projection(float new_fov, float new_near, float new_far);
    float get_fov();
    float get_near();
    float get_far();

};

class Camera{
    private:
    Point position;
    Point lookAt;
    Point up; // vetor
    Projection projection;

    public:
    Camera(Point new_position, Point new_lookAt, Point new_up, Projection new_projection);
    Point get_position();
    Point get_lookAt();
    Point get_up();
    Projection get_projection();
};

class Group{
    private:
    vector<Model> models;

    public:
    Group(vector<Model> new_models);
};

class World{
    private:
    Window window;
    Camera camera;
    Group group;

    public:
    World(Window new_window, Camera new_camera, Group new_group);
    Window get_window();
    Camera get_camera();
    Group get_group();
};

#endif