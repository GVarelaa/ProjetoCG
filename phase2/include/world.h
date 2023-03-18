#ifndef __WORLD__
#define __WORLD__

#include <vector>
#include "point.h"
#include "vbo.h"
#include "group.h"
#include "settings.h"
#include "tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class World{
    public:
        Window window;
        Camera camera;
        Group group;
        World();
        World(Window newWindow, Camera newCamera, Group newGroup);
        World(char *path);
        void loadGroup();
};

#endif