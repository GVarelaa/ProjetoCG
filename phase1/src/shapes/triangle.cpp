#include "../../include/triangle.h"

Triangle::Triangle(int indxx, int indyy, int indzz){
    indx = indxx;
    indy = indyy;
    indz = indzz;
}

int Triangle::getIndX(){
    return indx;
}

int Triangle::getIndY(){
    return indy;
}

int Triangle::getIndZ(){
    return indz;
}


