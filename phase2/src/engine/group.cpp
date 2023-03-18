#include "../../include/group.h"

Group::Group(){}

Group::Group(vector<VBO> newVBOS){
    vbos = newVBOS;
}

Group::Group(vector<string> newModelsPaths){
    modelsPaths = newModelsPaths;
}