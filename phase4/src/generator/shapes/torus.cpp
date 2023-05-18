#include "../../../include/generator/torus.h"

void generateTorus(float radiusIn, float radiusOut, int slices, int stacks, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals){
    float sliceAngle = (2 * M_PI) / slices;
    float stackAngle = (2 * M_PI) / stacks;

    int index = 0;
    for(int i = 0; i < slices; i++){
        for(int j = 0; j <= stacks; j++){
            Point p1 = Point((radiusOut + radiusIn*cos(j*stackAngle))*cos(i*sliceAngle), radiusIn * sin(j*stackAngle), (radiusOut + radiusIn*cos(j*stackAngle))*sin(i*sliceAngle));
            Point p2 = Point((radiusOut + radiusIn*cos(j*stackAngle))*cos((i+1)*sliceAngle), radiusIn * sin(j*stackAngle), (radiusOut + radiusIn*cos(j*stackAngle))*sin((i+1)*sliceAngle));
            vertices->push_back(p1);
            vertices->push_back(p2);

            Point n1 = Point(cos(j*stackAngle)*cos(i*sliceAngle), sin(j*stackAngle), cos(j*stackAngle)*sin(i*sliceAngle));
            Point n2 = Point(cos(j*stackAngle)*cos((i+1)*sliceAngle), sin(j*stackAngle), cos(j*stackAngle)*sin((i+1)*sliceAngle));
            normals->push_back(n1);
            normals->push_back(n2);

            if(j!=stacks){
                Triangle t1 = Triangle(index, index+1, index+2);
                Triangle t2 = Triangle(index+1, index + 3, index + 2);

                triangles->push_back(t1);
                triangles->push_back(t2);
            }
            index+=2;
        }
    }
}
