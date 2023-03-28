#ifndef __GROUP__
#define __GROUP__

#include <vector>
#include <string.h>
#include "model.h"
#include "transform.h"
#include "../point.h"
#include "../tinyxml2/tinyxml2.h"

using namespace tinyxml2;
using namespace std;

class Group{
    public:
        vector<Group> groups;
        vector<Model> models;
        vector<Transform *> transforms;
        Point color;

        Group();
        Group(XMLElement *groupElement);
        void loadModels();
        void drawModels();
};

#endif