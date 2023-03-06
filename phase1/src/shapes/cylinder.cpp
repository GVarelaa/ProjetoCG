#include "../../include/cylinder.h"

Model generateCylinder(float radius, float height, int slices) {
    vector<Point> points;
    vector<Triangle> triangles;

    float h_2 = height / 2.0;
    float alpha = (2 * M_PI) / slices;

    points.push_back(Point(0, h_2, 0)); // indice 0
    points.push_back(Point(0, -h_2, 0)); // indice 1

    for(int i = 0; i <= slices; i++){
        Point p1 = Point(radius * sin(i*alpha), h_2, radius * cos(i*alpha));
        Point p2 = Point(radius * sin(i*alpha), -h_2, radius * cos(i*alpha));
        points.push_back(p1);
        points.push_back(p2);

        if(i!=slices){
            // base superior 
            Triangle t1 = Triangle(0, 2 + i*2, 2 + (i+1)*2);
            triangles.push_back(t1);

            //base inferior
            Triangle t2 = Triangle(3 + (i+1)*2, 3 + i*2, 1);
            triangles.push_back(t2);

            //faces
            Triangle t3 = Triangle(2 + (i+1)*2, 2 + i*2, 3 + (i+1)*2);
            Triangle t4 = Triangle(2 + i*2, 3 + i*2, 3 + (i+1)*2);
            triangles.push_back(t3);
            triangles.push_back(t4);
        }
	}

    return Model(points, triangles);
}