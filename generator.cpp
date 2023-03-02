#include <string.h>
#include "headers/point.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

vector<Point *> generate_square(Point* point, float length){
    vector<Point *> vetor;

    float x = point->getX();
    float y = point->getY();
    float z = point->getZ();

    // primeiro triangulo
    Point* p1 = new Point(x, y, z);
    Point* p2 = new Point(x, y, z-length);
    Point* p3 = new Point(x-length, y, z);

    // segundo triangulo
    Point* p4 = new Point(x, y, z-length);
    Point* p5 = new Point(x-length, y, z-length);
    Point* p6 = new Point(x-length, y, z);

    vetor.push_back(p1);
    vetor.push_back(p2);
    vetor.push_back(p3);
    vetor.push_back(p4);
    vetor.push_back(p5);
    vetor.push_back(p6);

    return vetor;
}

vector<Point *> generate_plane(float length, int divisions){
    vector<Point *> points;

    float square_length = length/divisions;
    float initial_x = length/2.0;
    float initial_z = length/2.0;

    for(int i = 0; i < divisions; i++){
        float z_aux = initial_z;
        for(int j = 0; j < divisions; j++){
            vector<Point *> square_points = generate_square(new Point(initial_x, 0, z_aux), square_length);
            points.insert(points.end(), square_points.begin(), square_points.end());

            z_aux -= length/divisions;
        }

        initial_x -= length/divisions;
    }


    return points;
}

void write_vertices(vector<Point *> points, char* path){
    ofstream file; 
    file.open (path);

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
        //generate_box();
    }
    else if(regex_match(inp, regex(er_cone))){
        //generate_cone();
    }
    else if(regex_match(inp, regex(er_sphere))){
        //generate_sphere();
    }
    else {
        printf("%s\n", "Invalid input!");
    }

    //write_vertices();

    return 0;
}