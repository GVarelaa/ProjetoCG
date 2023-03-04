#ifndef __WORLD__
#define __WORLD__

#include "../point.h"
#include "../model.h"
#include <vector>
using namespace std;

class Window{
    private:
    int width;
    int height;

    public:
    int get_width();
    int get_height();
};

class Projection{
    private:
    float fov;
    float near;
    float far;

    public:
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
    Point get_position();
    Point get_lookAt();
    Point get_up();
    Projection get_projection();
};

class Group{
    private:
    vector<Model> models;
};

class World{
    private:
    Window window;
    Camera camera;
    Group group;

    public:
    Window get_window();

};



#endif