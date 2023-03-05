#include "../../include/plane.h"

vector<Triangle> generateSquare(int iterX, int iterZ, int divisions){
    vector<Triangle> triangles;

    int bottomLeftIndex = (divisions+1)*iterX + iterZ;
    int bottomRightIndex = (divisions+1)*(iterX+1) + iterZ;
    int topLeftIndex = (divisions+1)*iterX + (iterZ+1);
    int topRightIndex = (divisions+1)*(iterX+1) + (iterZ+1);

    Triangle t1 = Triangle(bottomLeftIndex, bottomRightIndex, topRightIndex);
    Triangle t2 = Triangle(bottomLeftIndex, topRightIndex, topLeftIndex);
    
    triangles.push_back(t1);
    triangles.push_back(t2);

    return triangles;
}

Model generatePlane(float length, int divisions){
    vector<Point> vertices;
    vector<Triangle> triangles;

    float squareLength = length/divisions;
    float initialX = length/2.0;
    float initialZ = length/2.0;

    float x = initialX;
    float z = initialZ;

    for(int i = 0; i <= divisions; i++){
        x = initialX;
        z = initialZ - i*squareLength;
        
        for(int j = 0; j <= divisions; j++){
            x = initialX - j*squareLength;
            vertices.push_back(Point(x, 0, z));

            if (i != divisions && j != divisions){
                vector<Triangle> squareTriangles = generateSquare(i, j, divisions);
                triangles.insert(triangles.end(), squareTriangles.begin(), squareTriangles.end());
            }
        }
    }

    return Model(vertices, triangles);
}