#include <math.h>
#include "headers/cone.h"


vector<Point *> generate_cone_base(float radius, int slices){
    vector<Point *> points;

    float alpha = (2 * M_PI) / slices;
    for(int i = 0; i < slices; i++){
        Point *p1 = new Point(0, 0, 0);
        Point *p2 = new Point(radius * sin((i+1)*alpha), 0, radius * cos((i+1)*alpha));
        Point *p3 = new Point(radius * sin(i*alpha), 0, radius * cos(i*alpha));

        points.push_back(p1);
        points.push_back(p2);
        points.push_back(p3);
    }

    return points;
}

vector<Point *> generate_cone_faces(float radius, float height, int slices, int stacks){
    vector<Point *> points;

    float alpha = (2 * M_PI) / slices;
    float h_part = height / stacks;
    float r_part = radius / stacks;
    
    for(int i = 0; i < slices; i++){
        for(int j = 0; j < stacks; j++){
            Point *p1 = new Point((radius - j*r_part) * sin(i*alpha), j*h_part, (radius - j*r_part) * cos(i*alpha));
            Point *p2 = new Point((radius - j*r_part) * sin((i+1)*alpha), j*h_part, (radius - j*r_part) * cos((i+1)*alpha));
            Point *p3 = new Point((radius - (j+1)*r_part) * sin(i*alpha), (j+1)*h_part, (radius - (j+1)*r_part) * cos(i*alpha));

            Point *p4 = new Point((radius - j*r_part) * sin((i+1)*alpha), j*h_part, (radius - j*r_part) * cos((i+1)*alpha));
            Point *p5 = new Point((radius - (j+1)*r_part) * sin((i+1)*alpha), (j+1)*h_part, (radius - (j+1)*r_part) * cos((i+1)*alpha));
            Point *p6 = new Point((radius - (j+1)*r_part) * sin(i*alpha), (j+1)*h_part, (radius - (j+1)*r_part) * cos(i*alpha));

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


vector<Point *> generate_cone(float radius, float height, int slices, int stacks){
    vector<Point *> points;

    vector<Point *> base_points = generate_cone_base(radius, slices);
    vector<Point *> face_points = generate_cone_faces(radius, height, slices, stacks);

    points.insert(points.end(), base_points.begin(), base_points.end());
    points.insert(points.end(), face_points.begin(), face_points.end());

    return points;
}

