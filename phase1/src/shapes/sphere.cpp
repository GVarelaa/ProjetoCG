#include <math.h>
#include "../../include/sphere.h"

Model generateSphere(float radius, int slices, int stacks){
    vector<Point> points;
    vector<Triangle> triangles;

    float alpha = (2 * M_PI) / slices;
    float beta = M_PI / stacks;

    //Ponto superior e inferior
    points.push_back(Point(0, -radius, 0));
    points.push_back(Point(0, radius, 0));

    for(int i = 0; i < slices; i++){
        if(i==slices-1){
            Triangle t1 = Triangle(0, 2, i*(stacks-1) + 2);
            Triangle t2 = Triangle(1, i*(stacks-1) + stacks, stacks);
            triangles.push_back(t1);
            triangles.push_back(t2);
        }
        else{
            Triangle t1 = Triangle(0, (i+1)*(stacks-1) + 2, i*(stacks-1) + 2);
            Triangle t2 = Triangle(1, i*(stacks-1) + stacks, (i+1)*(stacks-1) + stacks);
            triangles.push_back(t1);
            triangles.push_back(t2);
        }

        for(int j = 1; j < stacks; j++){
            Point p = Point(radius * cos(j*beta-M_PI_2) * sin(i*alpha), radius * sin(j*beta-M_PI_2), radius * cos(j*beta-M_PI_2) * cos(i*alpha));
            points.push_back(p);
        
            if(j!=stacks-1){
                if(i==slices-1){
                    Triangle t1 = Triangle(i*(stacks-1) + j + 1, j + 1, i*(stacks-1) + j + 2);
                    Triangle t2 = Triangle(j + 1, j + 2, i*(stacks-1) + j+2);

                    triangles.push_back(t1);
                    triangles.push_back(t2);
                }
                else{
                    Triangle t1 = Triangle(i*(stacks-1) + j + 1, (i+1)*(stacks-1) + j + 1, i*(stacks-1) + j + 2);
                    Triangle t2 = Triangle((i+1)*(stacks-1) + j + 1, (i+1)*(stacks-1) + j + 2, i*(stacks-1) + j+2);

                    triangles.push_back(t1);
                    triangles.push_back(t2);
                }
            }
        }
    }

    return Model(points, triangles);
}

