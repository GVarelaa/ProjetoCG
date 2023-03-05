#include <math.h>
#include "../../include/sphere.h"

Model generateSphere(float radius, int slices, int stacks){
    vector<Point> points;
    vector<Triangle> triangles;

    float alpha = (2 * M_PI) / slices;
    float beta = M_PI / stacks;

    for(int i = 0; i <= slices; i++){
        for(int j = 0; j <= stacks; j++){
            Point p = Point(radius * cos(j*beta-M_PI_2) * sin(i*alpha), radius * sin(j*beta-M_PI_2), radius * cos(j*beta-M_PI_2) * cos(i*alpha));

            points.push_back(p);

            if (i != slices && j != stacks){
                Triangle t1 = Triangle(i*(stacks+1) + j, (i+1)*(stacks+1) + j, i*(stacks+1) + j+1);
                Triangle t2 = Triangle((i+1)*(stacks+1) + j, (i+1)*(stacks+1) + j+1, i*(stacks+1) + j+1);

                triangles.push_back(t1);
                triangles.push_back(t2);
            }
        }
    }

    return Model(points, triangles);
}

