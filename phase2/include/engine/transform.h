#ifndef __TRANSFORM__
#define __TRANSFORM__

#include "../tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class Transform{
    public:
        float x;
        float y;
        float z;
};

class Translate : public Transform{
    public:
        Translate(float x, float y, float z);
        Translate(XMLElement *elem);
};

class Rotate : public Transform{
    public:
        float angle;

        Rotate(float x, float y, float z, float angle);
        Rotate(XMLElement *elem);
};

class Scale : public Transform{
    public:
        Scale(float x, float y, float z);
        Scale(XMLElement *elem);
};

#endif

