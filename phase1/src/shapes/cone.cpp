#include <math.h>
#include "../../include/cone.h"


pair<vector<Point>, vector<Triangle> > generate_cone_base(float radius, int slices, int *index){
    vector<Point> points;
    vector<Triangle> triangles;

    float alpha = (2 * M_PI) / slices;
    Point centralPoint = Point(0 , 0, 0);

    points.push_back(centralPoint);

    //Vértices
    for(int i = 0; i < slices; i++){
        Point p = Point(radius * sin(i*alpha), 0, radius * cos(i*alpha));
        points.push_back(p);
    }

    //Triângulos
    for(int i = 0; i < slices; i++){
        Triangle t = Triangle(i+2, i+1, 0);
        triangles.push_back(t);
    }

    *index += points.size();
    return pair<vector<Point>, vector<Triangle> >(points, triangles);
}

pair<vector<Point>, vector<Triangle> > generate_cone_faces(float radius, float height, int slices, int stacks, int *index){
    vector<Point> points;
    vector<Triangle> triangles;

    float alpha = (2 * M_PI) / slices;
    float h_part = height / stacks;
    float r_part = radius / stacks;
    
    for(int i = 0; i <= slices; i++){
        for(int j = 0; j <= stacks; j++){
            Point p = Point((radius - j*r_part) * sin(i*alpha), j*h_part, (radius - j*r_part) * cos(i*alpha));
            points.push_back(p);

            if(i != slices && j != stacks){
                Triangle t1 = Triangle(i*(stacks+1) + j + *index, (i+1)*(stacks+1) + j + *index, i*(stacks+1) + j+1 + *index);
                Triangle t2 = Triangle((i+1)*(stacks+1) + j + *index, (i+1)*(stacks+1) + j+1 + *index, i*(stacks+1) + j+1 + *index);
                triangles.push_back(t1);
                triangles.push_back(t2);
            }
        }
    }

    *index += points.size();
    return pair<vector<Point>, vector<Triangle> >(points, triangles);
}


Model generate_cone(float radius, float height, int slices, int stacks){
    vector<Point> points;
    vector<Triangle> triangles;
    int index=0;

    pair<vector<Point>, vector<Triangle> > base = generate_cone_base(radius, slices, &index);
    pair<vector<Point>, vector<Triangle> > faces = generate_cone_faces(radius, height, slices, stacks, &index);

    points.insert(points.end(), base.first.begin(), base.first.end());
    points.insert(points.end(), faces.first.begin(), faces.first.end());

    triangles.insert(triangles.end(), base.second.begin(), base.second.end());
    triangles.insert(triangles.end(), faces.second.begin(), faces.second.end());

    return Model(points, triangles);
}

