#include "../../include/plane.h"

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
