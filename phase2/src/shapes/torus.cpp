#include "../../include/torus.h"

Model generateTorus(float radiusIn, float radiusOut, int slices, int layers){
    vector<Point> vertices;
    vector<Triangle> triangles;

    float sliceAngle = (2 * M_PI) / slices;
    float layerAngle = (2 * M_PI) / layers;

    for(int i = 0; i < slices; i++){
        for(int j = 0; j <= layers; j++){
            Point p1 = Point((radiusOut + radiusIn*cos(j*layerAngle))*cos(i*sliceAngle), radiusIn * sin(j*layerAngle), (radiusOut + radiusIn*cos(j*layerAngle))*sin(i*sliceAngle));
            Point p2 = Point((radiusOut + radiusIn*cos(j*layerAngle))*cos((i+1)*sliceAngle), radiusIn * sin(j*layerAngle), (radiusOut + radiusIn*cos(j*layerAngle))*sin((i+1)*sliceAngle));

            vertices.push_back(p1);
            vertices.push_back(p2);
            if(j!=layers){
                Triangle t1 = Triangle(i*(2*layers + 2) + j*2, i*(2*layers + 2) + j*2 + 1, i*(2*layers + 2) + j*2 + 2);
                Triangle t2 = Triangle(i*(2*layers + 2) + j*2 + 1, i*(2*layers + 2) + j*2 + 3, i*(2*layers + 2) + j*2 + 2);

                triangles.push_back(t1);
                triangles.push_back(t2);
            }

        }
    }

    return Model(vertices, triangles);
}
