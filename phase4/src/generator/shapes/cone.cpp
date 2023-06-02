#include "../../../include/generator/cone.h"

void generateCone(float radius, float height, int slices, int stacks, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals, vector<Point> *texCoords){
    float alpha = (2 * M_PI) / slices;
    float hPart = height / stacks;
    float rPart = radius / stacks;

    int index = 0;
    for(int i = 0; i < slices; i++){
        // Base
        vertices->push_back(Point(0, 0, 0));
        vertices->push_back(Point(radius * sin(i*alpha), 0, radius * cos(i*alpha)));
        vertices->push_back(Point(radius * sin((i+1)*alpha), 0, radius * cos((i+1)*alpha)));
        
        for(int k = 0; k < 3; k++)
            normals->push_back(Point(0, -1, 0));

        triangles->push_back(Triangle(index+2, index+1, index));

        index+=3;

        for(int j = 0; j < stacks; j++){
            Point p1 = Point((radius - j*rPart) * sin(i*alpha), j*hPart, (radius - j*rPart) * cos(i*alpha));
            Point p2 = Point((radius - j*rPart) * sin((i+1)*alpha), j*hPart, (radius - j*rPart) * cos((i+1)*alpha));
            vertices->push_back(p1);
            vertices->push_back(p2);

            if(j!=stacks-1){
                Triangle t1 = Triangle(index, index+1, index+2);
                Triangle t2 = Triangle(index+1, index+3, index+2);
                triangles->push_back(t1);
                triangles->push_back(t2);

                index+=2;
            }
        }

        vertices->push_back(Point(0, height, 0));
        triangles->push_back(Triangle(index, index+1, index+2));

        index+=3;
    }
}

