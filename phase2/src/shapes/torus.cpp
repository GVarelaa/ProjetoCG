#include "../../include/torus.h"

Model generateTorus(float radiusIn, float radiusOut, int slices, int layers){
    vector<Point> vertices;
    vector<Triangle> triangles;

    float sliceAngle = (2 * M_PI) / slices;
    float layerAngle = (2 * M_PI) / layers;

    for(int i = 0; i < slices; i++){
        for(int j = 0; j <= layers; j++){
            float x = (radiusIn + radiusOut*cos(j*layerAngle))*cos(i*sliceAngle);
            float y = (radiusIn + radiusOut*cos(j*layerAngle))*sin(i*sliceAngle);
            float z = radiusOut * sin(j*layerAngle);

            Point p1 = Point((radiusIn + radiusOut*cos(j*layerAngle))*cos(i*sliceAngle), (radiusIn + radiusOut*cos(j*layerAngle))*sin(i*sliceAngle), radiusOut * sin(j*layerAngle));
            Point p2 = Point((radiusIn + radiusOut*cos(j*layerAngle))*cos((i+1)*sliceAngle), (radiusIn + radiusOut*cos(j*layerAngle))*sin((i+1)*sliceAngle), radiusOut * sin(j*layerAngle));

            vertices.push_back(p1);
            vertices.push_back(p2);

            if(j!=layers){
                Triangle t1 = Triangle(i*(2*layers) + j*2, i*(2*layers) + j*2 + 1, i*(2*layers) + j*2 + 2);
                Triangle t2 = Triangle(i*(2*layers) + j*2 + 1, i*(2*layers) + j*2 + 3, i*(2*layers) + j*2 + 2);
            }

        }
    }

    return Model(vertices, triangles);
}
