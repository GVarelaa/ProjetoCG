#include "../../include/triangle.h"

Triangle::Triangle(){
    
}

Triangle::Triangle(int new_indP1, int new_indP2, int new_indP3){
    indP1 = new_indP1;
    indP2 = new_indP2;
    indP3 = new_indP3;
}

int Triangle::getIndP1(){
    return indP1;
}

int Triangle::getIndP2(){
    return indP2;
}

int Triangle::getIndP3(){
    return indP3;
}


