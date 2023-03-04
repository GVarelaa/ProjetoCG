#include "../include/model.h"

Model::Model(vector<Point> new_points, vector<Triangle> new_triangles){
    points = new_points;
    triangles = new_triangles;
}

vector<Point> Model::getPoints(){
    return points;
}

vector<Triangle> Model::getTriangles(){
    return triangles;
}
