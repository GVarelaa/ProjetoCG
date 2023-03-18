#ifndef __GROUP__
#define __GROUP__

#include <vector>
#include <string.h>
#include "vbo.h"

class Group{
    public:
        vector<string> modelsPaths;
        vector<VBO> vbos;
        Group();
        Group(vector<VBO> vbos);
        Group(vector<string> modelsPaths);
};

#endif