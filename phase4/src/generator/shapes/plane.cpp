#include "../../../include/generator/plane.h"


void generatePlane(float length, int divisions, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals, vector<Point> *texCoords){
    float squareLength = length/divisions;
    float initialX = length/2.0;
    float initialZ = length/2.0;

    float x = initialX;
    float z = initialZ;

    int index=0;
    for(int i = 0; i < divisions; i++){
        x = initialX;
        z = initialZ - i*squareLength;
        
        for(int j = 0; j < divisions; j++){
            x = initialX - j*squareLength;

            vertices->push_back(Point(x, 0, z));
            vertices->push_back(Point(x, 0, z-squareLength));
            vertices->push_back(Point(x-squareLength, 0, z-squareLength));
            vertices->push_back(Point(x-squareLength, 0, z));

            for(int z = 0; z < 4; z++)
                normals->push_back(Point(0, 1, 0));

            texCoords->push_back(Point(i, j, 0));
            texCoords->push_back(Point(i+1, j, 0));
            texCoords->push_back(Point(i+1, j+1, 0));
            texCoords->push_back(Point(i, j+1, 0));

            triangles->push_back(Triangle(index, index+1, index+2));
            triangles->push_back(Triangle(index, index+2, index+3));

            index+=4;
        }
    }
}