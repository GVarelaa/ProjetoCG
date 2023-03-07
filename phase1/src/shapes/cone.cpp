#include "../../include/cone.h"

Model generateCone(float radius, float height, int slices, int stacks){
    vector<Point> points;
    vector<Triangle> triangles;

    float alpha = (2 * M_PI) / slices;
    float hPart = height / stacks;
    float rPart = radius / stacks;
    
    Point centralPoint = Point(0, 0, 0);
    Point topPoint = Point(0, height, 0);
    points.push_back(centralPoint);
    points.push_back(topPoint);

    for(int i = 0; i < slices; i++){
        if(i==slices-1){
            Triangle base_triangle = Triangle(i*stacks + 2 , 0, 2);
            Triangle top_triangle = Triangle(i*stacks + 1 + stacks, stacks + 1, 1);
            triangles.push_back(base_triangle);
            triangles.push_back(top_triangle);
        }
        else{
            Triangle base_triangle = Triangle(i*stacks + 2, 0, (i+1)*stacks + 2);
            Triangle top_triangle = Triangle(i*stacks + 1 + stacks, (i+1)*stacks + 1 + stacks, 1);
            triangles.push_back(base_triangle);
            triangles.push_back(top_triangle);
        }

        for(int j = 0; j < stacks; j++){
            Point p = Point((radius - j*rPart) * sin(i*alpha), j*hPart, (radius - j*rPart) * cos(i*alpha));
            points.push_back(p);

            if(j!=stacks-1){
                if(i==slices-1){
                    Triangle t1 = Triangle(i*stacks + j + 2, j + 2, i*stacks + j + 2 + 1);
                    Triangle t2 = Triangle(j + 2, j+ 2 + 1, i*stacks + j + 2 + 1);
                    triangles.push_back(t1);
                    triangles.push_back(t2); 
                }
                else{
                    Triangle t1 = Triangle(i*stacks + j + 2, (i+1)*stacks + j + 2, i*stacks + j + 1 + 2);
                    Triangle t2 = Triangle((i+1)*stacks + j + 2, (i+1)*stacks + j + 2 + 1, i*stacks + j + 2 + 1);
                    triangles.push_back(t1);
                    triangles.push_back(t2);
                }
            }
        }
    }

    return Model(points, triangles);
}

