#ifndef __WORLD__
#define __WORLD__

#include <vector>
#include "point.h"
#include "model.h"
#include "tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class Window{
    public:
        int width;
        int height;
        Window();
        Window(int new_height, int new_width);
        int get_width();
        int get_height();
};

class Projection{
    public:
        float fov;
        float near;
        float far;
        Projection();
        Projection(float new_fov, float new_near, float new_far);
        float get_fov();
        float get_near();
        float get_far();
};

class Camera{
    public:
        Point position;
        Point lookAt;
        Point up; // vetor
        Projection projection;
        Camera();
        Camera(Point new_position, Point new_lookAt, Point new_up, Projection new_projection);
        Point get_position();
        Point get_lookAt();
        Point get_up();
        Projection get_projection();
};

class Group{
    public:
        vector<Model> models;
        Group();
        Group(vector<Model> new_models);
};

class World{
    public:
        Window window;
        Camera camera;
        Group group;
        World();
        World(Window new_window, Camera new_camera, Group new_group);
        World(char *path);
        void parser(char *path);
};

#endif