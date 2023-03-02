#ifndef __POINT__
#define __POINT__


class Point { 
    private:   
        float x;  
        float y;  
        float z;

    public:
        Point(float x1, float y1, float z1);
        float getX();
        float getY();
        float getZ();
        void setX(float x1);
        void setY(float y1);
        void setZ(float z1);
};

#endif