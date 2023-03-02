#include <string.h>
#include "headers/point.h"
#include "headers/plane.h"
#include "headers/box.h"
#include "headers/cone.h"
#include "headers/sphere.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

void write_vertices(vector<Point *> points, char* path){
    ofstream file; 
    file.open(path);

    char buffer[1024];
    for(int i = 0; i < points.size(); i++){
        Point* point = points[i];
        sprintf(buffer, "%f %f %f\n", point->getX(), point->getY(), point->getZ());
        file << buffer;
    }

    file.close();
}


int main(int argc, char *argv[]){
    string inp;

    for (int i=1; argv[i] != NULL; i++) {
        inp.append(argv[i]);
        inp.push_back(' ');
    }
    inp.pop_back();

    char er_plane[] = "plane [0-9]+ [0-9]+ [a-zA-Z0-9_]+.3d$";
    char er_box[] = "box [0-9]+ [0-9]+ [a-zA-Z0-9_]+.3d$";
    char er_cone[] = "cone [0-9]+ [0-9]+ [0-9]+ [0-9]+ [a-zA-Z0-9_]+.3d$";
    char er_sphere[] = "sphere [0-9]+ [0-9]+ [0-9]+ [a-zA-Z0-9_]+.3d$";

    if (regex_match(inp, regex(er_plane))){
        float length = atof(argv[2]);
        int divisions = atoi(argv[3]);
        char* file_path = argv[4];
        vector<Point *> points = generate_plane(length, divisions);

        write_vertices(points, file_path);
    }
    else if(regex_match(inp, regex(er_box))){
        float length = atof(argv[2]);
        int divisions = atoi(argv[3]);
        char* file_path = argv[4];
        vector<Point *> points = generate_box(length, divisions);

        write_vertices(points, file_path);
    }
    else if(regex_match(inp, regex(er_cone))){
        float radius = atof(argv[2]);
        float height = atof(argv[3]);
        int slices = atoi(argv[4]);
        int stacks = atoi(argv[5]);
        char* file_path = argv[6];
        vector<Point *> points = generate_cone(radius, height, slices, stacks);

        write_vertices(points, file_path);
    }
    else if(regex_match(inp, regex(er_sphere))){
        float radius = atof(argv[2]);
        int slices = atoi(argv[3]);
        int stacks = atoi(argv[4]);
        char* file_path = argv[5];
        vector<Point *> points = generate_sphere(radius, slices, stacks);

        write_vertices(points, file_path);
    }
    else {
        printf("%s\n", "Invalid input!");
    }

    //write_vertices();

    return 0;
}