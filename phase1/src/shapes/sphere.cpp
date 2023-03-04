#include <math.h>
#include "../../include/sphere.h"

vector<Point> generate_sphere(float radius, int slices, int stacks){
    vector<Point> points;

    float alpha = (2 * M_PI) / slices;
    float beta = M_PI / stacks;

    for(int i = 0; i < slices; i++){
        for(int j = 0; j < stacks; j++){
            Point p1 = Point(radius * cos(j*beta-M_PI_2) * sin(i*alpha), radius * sin(j*beta-M_PI_2), radius * cos(j*beta-M_PI_2) * cos(i*alpha));
            Point p2 = Point(radius * cos(j*beta-M_PI_2) * sin((i+1)*alpha), radius * sin(j*beta-M_PI_2), radius * cos(j*beta-M_PI_2) * cos((i+1)*alpha));
            Point p3 = Point(radius * cos((j+1)*beta-M_PI_2) * sin(i*alpha), radius * sin((j+1)*beta-M_PI_2), radius * cos((j+1)*beta-M_PI_2) * cos(i*alpha));
            
            Point p4 = Point(radius * cos(j*beta-M_PI_2) * sin((i+1)*alpha), radius * sin(j*beta-M_PI_2), radius * cos(j*beta-M_PI_2) * cos((i+1)*alpha));
            Point p5 = Point(radius * cos((j+1)*beta-M_PI_2) * sin((i+1)*alpha), radius * sin((j+1)*beta-M_PI_2), radius * cos((j+1)*beta-M_PI_2) * cos((i+1)*alpha));
            Point p6 = Point(radius * cos((j+1)*beta-M_PI_2) * sin(i*alpha), radius * sin((j+1)*beta-M_PI_2), radius * cos((j+1)*beta-M_PI_2) * cos(i*alpha));

            points.push_back(p1);
            points.push_back(p2);
            points.push_back(p3);
            points.push_back(p4);
            points.push_back(p5);
            points.push_back(p6);
        }
    }

    return points;
}

