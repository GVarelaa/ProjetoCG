#ifndef __GROUP__
#define __GROUP__

#include <vector>
#include <string.h>
#include "vbo.h"
#include "model.h"
#include "transform.h"

class Group{
    public:
        vector<Group> groups;
        vector<Model> models;
        vector<Transform> transforms;
        
        Group();
        Group(vector<VBO> vbos);
        Group(vector<string> modelsPaths);
};

#endif