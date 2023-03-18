#ifndef __GROUP__
#define __GROUP__

#include <vector>
#include <string.h>
#include "model.h"
#include "transform.h"
#include "../tinyxml2/tinyxml2.h"

using namespace tinyxml2;
using namespace std;

class Group{
    public:
        vector<Group> groups;
        vector<Model> models;
        vector<Transform> transforms;
        
        Group();
        Group(XMLElement *groupElement);
        Group(vector<Model> models);
        Group(vector<string> modelsPaths);
};

#endif