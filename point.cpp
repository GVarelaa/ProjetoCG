#include "headers/point.h"

Point::Point(float x1, float y1, float z1){
    x = x1;
    y = y1;
    z = z1;
}

float Point::getX(){
    return x;
}

float Point::getY(){
    return y;
}

float Point::getZ(){
    return z;
}

void Point::setX(float x1){
    x = x1;
}

void Point::setY(float y1){
    y = y1;
}

void Point::setZ(float z1){
    z = z1;
}



