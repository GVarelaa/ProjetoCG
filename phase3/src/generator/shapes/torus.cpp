#include "../../../include/generator/torus.h"

pair<vector<Point>, vector<Triangle> > generateTorus(float radiusIn, float radiusOut, int slices, int stacks){
    vector<Point> vertices;
    vector<Triangle> triangles;

    float sliceAngle = (2 * M_PI) / slices;
    float stackAngle = (2 * M_PI) / stacks;

    int index = 0;
    for(int i = 0; i < slices; i++){
        for(int j = 0; j <= stacks; j++){
            Point p1 = Point((radiusOut + radiusIn*cos(j*stackAngle))*cos(i*sliceAngle), radiusIn * sin(j*stackAngle), (radiusOut + radiusIn*cos(j*stackAngle))*sin(i*sliceAngle));
            Point p2 = Point((radiusOut + radiusIn*cos(j*stackAngle))*cos((i+1)*sliceAngle), radiusIn * sin(j*stackAngle), (radiusOut + radiusIn*cos(j*stackAngle))*sin((i+1)*sliceAngle));
            vertices.push_back(p1);
            vertices.push_back(p2);


            if(j!=stacks){
                Triangle t1 = Triangle(index, index+1, index+2);
                Triangle t2 = Triangle(index+1, index + 3, index + 2);

                triangles.push_back(t1);
                triangles.push_back(t2);
            }
            index+=2;
        }
    }

    return pair<vector<Point>, vector<Triangle> >(vertices, triangles);
}
